import pandas as pd
import json
import re

# Function to convert text to slug format (e.g. "Two Pointers" -> "two-pointers")
def slugify(text):
    if not isinstance(text, str):
        return ""
    text = text.lower().strip()
    # Replace non-alphanumeric chars (excluding hyphens) with empty string
    text = re.sub(r'[^\w\s-]', '', text)
    # Replace spaces and underscores with hyphens
    text = re.sub(r'[\s_-]+', '-', text)
    # Remove leading/trailing hyphens
    text = re.sub(r'^-+|-+$', '', text)
    return text

def convert_csv_to_json(csv_file, json_file):
    # Load the CSV
    df = pd.read_csv(csv_file)
    
    questions = []
    
    for _, row in df.iterrows():
        # Process Categories
        cats_raw = str(row.get('categories', ''))
        categories = [slugify(c) for c in cats_raw.split(',') if c.strip()]
        
        # Process Companies (Map companyTags -> companies)
        comps_raw = str(row.get('companyTags', ''))
        companies = [slugify(c) for c in comps_raw.split(',') if c.strip()]
        
        # Ensure Difficulty is capitalized (Easy, Medium, Hard)
        difficulty = str(row.get('difficulty', 'Medium')).capitalize()
        if difficulty not in ['Easy', 'Medium', 'Hard']:
            difficulty = 'Medium'

        # Construct Question Object
        question = {
            "title": row.get('title', ''),
            "slug": row.get('slug', ''),
            "description": row.get('description', ''),
            "difficulty": difficulty,
            "externalPlatformUrl": row.get('externalPlatformUrl', ''),
            "solutionUrl": row.get('solutionUrl', ''),
            "categories": categories,
            "companies": companies
        }
        questions.append(question)
    
    # Save to JSON
    with open(json_file, 'w', encoding='utf-8') as f:
        json.dump(questions, f, indent=2)
    
    print(f"Successfully converted {len(questions)} questions to {json_file}")

# Run the conversion
convert_csv_to_json('arsh_dsa_sheet.csv', 'questions_bulk_upload.json')