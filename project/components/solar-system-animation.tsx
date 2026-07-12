import { useEffect, useRef } from 'react';

export default function SolarSystem() {
  const canvasRef = useRef(null);

  useEffect(() => {
    const canvas = canvasRef.current;
    const ctx = canvas.getContext('2d');
    let animationFrameId;
    let time = 0;

    const centerX = canvas.width / 2;
    const centerY = canvas.height / 2;

    const planets = [
      { name: 'Mercury', distance: 60, size: 4, color: '#8C7853', speed: 0.04 },
      { name: 'Venus', distance: 85, size: 7, color: '#FFC649', speed: 0.03 },
      { name: 'Earth', distance: 115, size: 8, color: '#4A90E2', speed: 0.02 },
      { name: 'Mars', distance: 145, size: 6, color: '#E27B58', speed: 0.018 },
      { name: 'Jupiter', distance: 200, size: 16, color: '#C88B3A', speed: 0.01 },
      { name: 'Saturn', distance: 250, size: 14, color: '#FAD5A5', speed: 0.008 },
      { name: 'Uranus', distance: 290, size: 10, color: '#4FD0E7', speed: 0.006 },
      { name: 'Neptune', distance: 320, size: 10, color: '#4166F5', speed: 0.005 }
    ];

    const drawSun = () => {
      const gradient = ctx.createRadialGradient(centerX, centerY, 0, centerX, centerY, 25);
      gradient.addColorStop(0, '#FFF76B');
      gradient.addColorStop(0.5, '#FFA500');
      gradient.addColorStop(1, '#FF6B00');
      
      ctx.fillStyle = gradient;
      ctx.beginPath();
      ctx.arc(centerX, centerY, 25, 0, Math.PI * 2);
      ctx.fill();
      
      // Sun glow
      ctx.fillStyle = 'rgba(255, 200, 0, 0.1)';
      ctx.beginPath();
      ctx.arc(centerX, centerY, 35, 0, Math.PI * 2);
      ctx.fill();
    };

    const drawOrbit = (distance) => {
      ctx.strokeStyle = 'rgba(255, 255, 255, 0.1)';
      ctx.lineWidth = 1;
      ctx.beginPath();
      ctx.arc(centerX, centerY, distance, 0, Math.PI * 2);
      ctx.stroke();
    };

    const drawPlanet = (planet, angle) => {
      const x = centerX + Math.cos(angle) * planet.distance;
      const y = centerY + Math.sin(angle) * planet.distance;

      // Planet shadow
      ctx.fillStyle = 'rgba(0, 0, 0, 0.3)';
      ctx.beginPath();
      ctx.arc(x + 1, y + 1, planet.size, 0, Math.PI * 2);
      ctx.fill();

      // Planet body
      const gradient = ctx.createRadialGradient(x - planet.size/3, y - planet.size/3, 0, x, y, planet.size);
      gradient.addColorStop(0, planet.color);
      gradient.addColorStop(1, adjustBrightness(planet.color, -40));
      
      ctx.fillStyle = gradient;
      ctx.beginPath();
      ctx.arc(x, y, planet.size, 0, Math.PI * 2);
      ctx.fill();

      // Saturn's rings
      if (planet.name === 'Saturn') {
        ctx.strokeStyle = 'rgba(218, 165, 32, 0.6)';
        ctx.lineWidth = 3;
        ctx.beginPath();
        ctx.ellipse(x, y, planet.size + 8, planet.size / 3, 0, 0, Math.PI * 2);
        ctx.stroke();
      }
    };

    const adjustBrightness = (color, amount) => {
      const hex = color.replace('#', '');
      const r = Math.max(0, Math.min(255, parseInt(hex.substr(0, 2), 16) + amount));
      const g = Math.max(0, Math.min(255, parseInt(hex.substr(2, 2), 16) + amount));
      const b = Math.max(0, Math.min(255, parseInt(hex.substr(4, 2), 16) + amount));
      return `rgb(${r}, ${g}, ${b})`;
    };

    const drawStars = () => {
      ctx.fillStyle = 'rgba(255, 255, 255, 0.8)';
      for (let i = 0; i < 100; i++) {
        const x = Math.random() * canvas.width;
        const y = Math.random() * canvas.height;
        const size = Math.random() * 1.5;
        ctx.beginPath();
        ctx.arc(x, y, size, 0, Math.PI * 2);
        ctx.fill();
      }
    };

    const animate = () => {
      ctx.fillStyle = '#000814';
      ctx.fillRect(0, 0, canvas.width, canvas.height);

      drawStars();

      planets.forEach(planet => {
        drawOrbit(planet.distance);
      });

      drawSun();

      planets.forEach(planet => {
        const angle = time * planet.speed;
        drawPlanet(planet, angle);
      });

      time += 1;
      animationFrameId = requestAnimationFrame(animate);
    };

    animate();

    return () => {
      cancelAnimationFrame(animationFrameId);
    };
  }, []);

  return (
    <div className="flex items-center justify-center min-h-screen bg-gray-900">
      <div className="text-center">
        <h1 className="text-4xl font-bold text-white mb-6">Solar System</h1>
        <canvas
          ref={canvasRef}
          width={700}
          height={700}
          className="border-2 border-gray-700 rounded-lg shadow-2xl"
        />
        <p className="text-gray-400 mt-4 text-sm">Planets orbit at relative speeds</p>
      </div>
    </div>
  );
}