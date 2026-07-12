import pygame
import sys
import simpy
import random
import math
from pygame import gfxdraw

# Initialize pygame
pygame.init()

# Constants
WIDTH, HEIGHT = 1200, 800
LAB_COLOR = (240, 240, 245)
PROFESSOR_TEACHING_COLOR = (0, 200, 0)  # Green when teaching
PROFESSOR_NORMAL_COLOR = (0, 0, 0)      # Black otherwise
STUDENT_WORKING_COLOR = (0, 200, 0)     # Green when working
STUDENT_DISCUSSING_COLOR = (0, 0, 200)  # Blue when discussing
STUDENT_CHATTING_COLOR = (200, 0, 0)    # Red when chatting
STUDENT_NORMAL_COLOR = (0, 0, 0)        # Black otherwise
STUDENT_ATTENDANCE_COLOR = (200, 200, 0) # Yellow during attendance
WASHROOM_COLOR = (150, 150, 150)
DESK_COLOR = (100, 100, 100)
TEXT_COLOR = (0, 0, 0)
BACKGROUND_COLOR = (255, 255, 255)
DESK_LINE_COLOR = (150, 150, 150)
SEAT_COLOR = (200, 200, 200)

# Create the screen
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Lab Simulation")
clock = pygame.time.Clock()
font = pygame.font.SysFont('Arial', 16)

class LabSimulation:
    def __init__(self, env):
        self.env = env
        self.minute = 1
        self.speed_factor = 1  # Simulation speed factor (0.01 = 100x slower)

        self.washroom = simpy.Resource(env, capacity=2)
        self.professor_desk = simpy.Resource(env, capacity=1)

        # Tracking variables
        self.professor_arrived = False
        self.professor_arrival_time = None
        self.teaching_started = False
        self.teaching_ended = False
        self.file_checking_started = False
        self.file_checking_ended = False
        self.attendance_taken = False
        self.class_ended = False
        self.current_attendance_student = None
        self.attendance_done = False

        self.students_present = 0
        self.total_students = 29
        self.student_ids = list(range(1, self.total_students + 1))
        self.active_students = set()
        self.kicked_out = set()
        self.absent_students = set()
        self.arrival_times = {}
        self.settled_times = {}
        self.chatting_students = set()
        self.discussing_students = set()
        self.washroom_users = set()
        self.file_check_queue = []
        self.students_at_desk = set()
        self.files_checked = set()  # Track which students had files checked

        # GUI positions
        self.professor_pos = (WIDTH // 2, 100)
        self.student_positions = {}
        self.student_target_positions = {}
        self.washroom_pos = (WIDTH - 150, HEIGHT // 2)
        self.desk_pos = (WIDTH // 2, 200)
        self.desk_queue_positions = [(self.desk_pos[0] - 60 + i*20, self.desk_pos[1] + 60) for i in range(5)]
        
        # Initialize student positions
        self.initialize_student_positions()

    def initialize_student_positions(self):
        # Arrange students in a grid
        cols = 6
        start_x = 100
        start_y = 300
        spacing = 150
        
        # Initial positions outside the lab (for arrival animation)
        for student_id in self.student_ids:
            self.student_positions[student_id] = (-50, random.randint(50, HEIGHT-50))
        
        # Target positions (seats)
        for i, student_id in enumerate(self.student_ids):
            row = i // cols
            col = i % cols
            x = start_x + col * spacing
            y = start_y + row * spacing
            self.student_target_positions[student_id] = (x, y)

    def professor(self):
        self.professor_arrival_time = random.randint(0, 10)
        yield self.env.timeout(self.professor_arrival_time * self.minute)
        self.professor_arrived = True

        while (self.students_present < 15 or
               self.env.now < (self.professor_arrival_time + 10) * self.minute):
            if self.students_present < 15:
                pass
            yield self.env.timeout(1 * self.minute)

        if self.students_present >= 15:
            self.teaching_started = True
            yield self.env.timeout(30 * self.minute)
            self.teaching_ended = True
        else:
            return

        while self.env.now < 60 * self.minute:
            if random.random() < 0.25 and self.active_students:
                student = random.choice(list(self.active_students))
                yield self.env.timeout(2 * self.minute)
            else:
                yield self.env.timeout(1 * self.minute)

        self.file_checking_started = True

        # File checking phase - ensure each student only gets checked once
        students_to_check = list(self.active_students - self.files_checked)
        for student_id in students_to_check:
            with self.professor_desk.request() as req:
                self.students_at_desk.add(student_id)
                # Move to queue position
                queue_pos = min(len(self.students_at_desk)-1, len(self.desk_queue_positions)-1)
                self.student_positions[student_id] = self.desk_queue_positions[queue_pos]
                
                yield req
                
                # Move to desk position
                self.student_positions[student_id] = (self.desk_pos[0], self.desk_pos[1] + 30)
                check_time = random.randint(1, 2) * self.minute
                yield self.env.timeout(check_time)
                
                # Return to seat and mark as checked
                self.student_positions[student_id] = self.student_target_positions[student_id]
                self.students_at_desk.remove(student_id)
                self.files_checked.add(student_id)

        self.file_checking_ended = True

        # Ensure all students are at their seats before attendance
        for student_id in self.active_students:
            self.student_positions[student_id] = self.student_target_positions[student_id]

        self.attendance_taken = True
        self.absent_students = set(self.student_ids) - self.active_students - self.kicked_out

        # Take attendance in order (1-29)
        for student_id in sorted(self.student_ids):
            self.current_attendance_student = student_id
            yield self.env.timeout(1 * self.minute)
            self.current_attendance_student = None

        self.attendance_done = True

        yield self.env.timeout(max(0, (115 - self.env.now)) * self.minute)
        self.class_ended = True

    def student(self, student_id):
        if random.random() > 0.8:
            self.absent_students.add(student_id)
            return

        arrival_time = random.randint(0, 12)
        yield self.env.timeout(arrival_time * self.minute)
        self.arrival_times[student_id] = self.env.now

        # Move student to their seat
        target_pos = self.student_target_positions[student_id]
        steps = 30  # Number of steps for movement animation
        for i in range(steps):
            if i == steps - 1:
                self.student_positions[student_id] = target_pos
            else:
                # Linear interpolation between current position and target
                current_x, current_y = self.student_positions[student_id]
                target_x, target_y = target_pos
                new_x = current_x + (target_x - current_x) * 0.1
                new_y = current_y + (target_y - current_y) * 0.1
                self.student_positions[student_id] = (new_x, new_y)
            yield self.env.timeout(0.1 * self.minute)

        if self.env.now > 12 * self.minute and self.professor_arrived:
            self.kicked_out.add(student_id)
            return

        settle_time = random.randint(2, 4)
        yield self.env.timeout(settle_time * self.minute)
        self.students_present += 1
        self.active_students.add(student_id)
        self.settled_times[student_id] = self.env.now

        while not self.teaching_ended and not self.class_ended:
            yield self.env.timeout(1 * self.minute)

        while not self.class_ended:
            if self.attendance_taken:
                yield self.env.timeout(1 * self.minute)
                continue

            # Don't do other activities if waiting for file check
            if student_id in self.students_at_desk:
                yield self.env.timeout(1 * self.minute)
                continue

            activity = random.random()

            if activity < 0.05:
                with self.washroom.request() as req:
                    self.washroom_users.add(student_id)
                    # Move to washroom area
                    self.student_positions[student_id] = (
                        self.washroom_pos[0] - 30 + random.randint(0, 60),
                        self.washroom_pos[1] - 30 + random.randint(0, 60)
                    )
                    yield req
                    yield self.env.timeout(random.randint(1, 3) * self.minute)
                    self.washroom_users.remove(student_id)
                    # Return to seat
                    self.student_positions[student_id] = self.student_target_positions[student_id]

            elif activity < 0.15:
                possible_partners = [s for s in self.active_students
                                     if s != student_id and s not in self.discussing_students and s not in self.students_at_desk]
                if possible_partners:
                    num_partners = min(2, len(possible_partners))
                    partners = random.sample(possible_partners, num_partners)
                    self.discussing_students.update([student_id] + partners)
                    
                    # Move students closer for discussion
                    original_positions = {s: self.student_positions[s] for s in [student_id] + partners}
                    center_x = sum(self.student_positions[s][0] for s in [student_id] + partners) / (num_partners + 1)
                    center_y = sum(self.student_positions[s][1] for s in [student_id] + partners) / (num_partners + 1)
                    
                    for i, s in enumerate([student_id] + partners):
                        angle = 2 * math.pi * i / (num_partners + 1)
                        self.student_positions[s] = (
                            center_x + 40 * math.cos(angle),
                            center_y + 40 * math.sin(angle)
                        )
                    
                    yield self.env.timeout(random.randint(5, 10) * self.minute)
                    self.discussing_students.difference_update([student_id] + partners)
                    
                    # Return to original positions
                    for s, pos in original_positions.items():
                        self.student_positions[s] = pos
                else:
                    yield self.env.timeout(1 * self.minute)

            elif activity < 0.18:
                possible_partners = [s for s in self.active_students
                                     if s != student_id and s not in self.chatting_students and s not in self.students_at_desk]
                if possible_partners:
                    num_partners = min(2, len(possible_partners))
                    partners = random.sample(possible_partners, num_partners)
                    self.chatting_students.update([student_id] + partners)
                    
                    # Move students closer for chatting
                    original_positions = {s: self.student_positions[s] for s in [student_id] + partners}
                    center_x = sum(self.student_positions[s][0] for s in [student_id] + partners) / (num_partners + 1)
                    center_y = sum(self.student_positions[s][1] for s in [student_id] + partners) / (num_partners + 1)
                    
                    for i, s in enumerate([student_id] + partners):
                        angle = 2 * math.pi * i / (num_partners + 1)
                        self.student_positions[s] = (
                            center_x + 40 * math.cos(angle),
                            center_y + 40 * math.sin(angle)
                        )
                    
                    yield self.env.timeout(random.randint(2, 4) * self.minute)
                    self.chatting_students.difference_update([student_id] + partners)
                    
                    # Return to original positions
                    for s, pos in original_positions.items():
                        self.student_positions[s] = pos
                else:
                    yield self.env.timeout(1 * self.minute)

            else:
                work_time = random.randint(5, 15) * self.minute
                yield self.env.timeout(work_time)

        # Student leaves when class ends
        if student_id in self.active_students:
            # Move off screen
            steps = 30
            for i in range(steps):
                current_x, current_y = self.student_positions[student_id]
                self.student_positions[student_id] = (current_x - 5, current_y)
                yield self.env.timeout(0.1 * self.minute)
            self.active_students.remove(student_id)

    def draw(self, screen):
        # Clear screen
        screen.fill(BACKGROUND_COLOR)
        
        # Draw lab area
        pygame.draw.rect(screen, LAB_COLOR, (50, 50, WIDTH-100, HEIGHT-100), border_radius=10)
        
        # Draw all 29 seats (even for absent students)
        for student_id, pos in self.student_target_positions.items():
            # Draw seat (chair symbol)
            pygame.draw.rect(screen, SEAT_COLOR, (pos[0]-15, pos[1]+20, 30, 5))
            pygame.draw.rect(screen, SEAT_COLOR, (pos[0]-5, pos[1]+10, 10, 10))
        
        # Draw washroom
        pygame.draw.rect(screen, WASHROOM_COLOR, (self.washroom_pos[0]-30, self.washroom_pos[1]-30, 60, 60))
        text = font.render("Washroom", True, TEXT_COLOR)
        screen.blit(text, (self.washroom_pos[0] - 35, self.washroom_pos[1] + 40))
        
        # Draw professor's desk
        pygame.draw.rect(screen, DESK_COLOR, (self.desk_pos[0]-40, self.desk_pos[1]-20, 80, 40))
        text = font.render("Desk", True, TEXT_COLOR)
        screen.blit(text, (self.desk_pos[0] - 20, self.desk_pos[1] + 30))
        
        # Draw file check queue positions
        for i, pos in enumerate(self.desk_queue_positions):
            pygame.draw.circle(screen, (220, 220, 220), pos, 5)
        
        # Draw students (as hollow circles)
        for student_id, pos in self.student_positions.items():
            if student_id in self.active_students or student_id in self.students_at_desk:
                # Determine student color
                if self.current_attendance_student == student_id:
                    color = STUDENT_ATTENDANCE_COLOR  # Yellow during attendance call
                elif student_id in self.chatting_students:
                    color = STUDENT_CHATTING_COLOR  # Red for chatting
                elif student_id in self.discussing_students:
                    color = STUDENT_DISCUSSING_COLOR  # Blue for discussing
                elif student_id in self.washroom_users:
                    color = STUDENT_NORMAL_COLOR  # Black for washroom
                else:
                    color = STUDENT_WORKING_COLOR  # Green for working
                
                # Draw hollow circle
                pygame.draw.circle(screen, color, pos, 15, 2)
                text = font.render(str(student_id), True, TEXT_COLOR)
                screen.blit(text, (pos[0] - 5, pos[1] - 8))
        
        # Draw professor (as filled circle)
        if self.professor_arrived:
            color = PROFESSOR_TEACHING_COLOR if self.teaching_started and not self.teaching_ended else PROFESSOR_NORMAL_COLOR
            pygame.draw.circle(screen, color, self.professor_pos, 20)
            text = font.render("Professor", True, TEXT_COLOR)
            screen.blit(text, (self.professor_pos[0] - 30, self.professor_pos[1] + 30))
        
        # Draw simulation time
        time_text = font.render(f"Time: {self.format_time(self.env.now)}", True, TEXT_COLOR)
        screen.blit(time_text, (20, 20))
        
        # Draw status
        status = []
        if self.professor_arrived:
            status.append("Professor arrived")
        if self.teaching_started:
            status.append("Teaching in progress")
        if self.file_checking_started:
            status.append("File checking")
        if self.attendance_taken:
            if self.current_attendance_student:
                status.append(f"Calling roll: {self.current_attendance_student}")
            else:
                status.append("Taking attendance")
        if self.class_ended:
            status.append("Class ended")
        
        for i, s in enumerate(status):
            text = font.render(s, True, TEXT_COLOR)
            screen.blit(text, (WIDTH - 200, 20 + i * 20))
        
        pygame.display.flip()

    def format_time(self, minutes):
        return f"{minutes//60}h {minutes%60}m"

def main():
    env = simpy.Environment()
    lab = LabSimulation(env)

    # Start simulation processes
    env.process(lab.professor())
    for student_id in lab.student_ids:
        env.process(lab.student(student_id))

    # Main game loop
    running = True
    last_time = pygame.time.get_ticks()
    
    while running:
        current_time = pygame.time.get_ticks()
        delta_time = current_time - last_time
        last_time = current_time
        
        # Handle events
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
        
        # Run simulation for a small step
        try:
            # Convert real milliseconds to simulation time
            sim_time = delta_time * lab.speed_factor
            env.run(until=env.now + sim_time / 1000)  # Convert to seconds
        except:
            pass  # Simulation ended
        
        # Draw everything
        lab.draw(screen)
        
        # Cap the frame rate
        clock.tick(60)
    
    pygame.quit()
    sys.exit()

if __name__ == "__main__":
    main()