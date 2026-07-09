import requests
import time

base_url = 'http://127.0.0.1:5000'

print('🔍 Testing Intent Matching with Dataset Patterns')
print('=' * 50)

# Test patterns from the dataset
test_cases = [
    ('Hi', 'greeting'),
    ('Book a table', 'book_table'),
    ('Available seats', 'available_tables'),
    ('Goodbye', 'goodbye'),
    ('what is your name', 'identity'),
    ('when are you guys open', 'hours'),
    ('whats on the menu', 'menu'),
    ('contact information', 'contact'),
    ('what is the location?', 'address'),
    ('the noodles were amazing', 'positive_feedback'),
    ('too salty', 'negative_feedback'),
    ('is it really safe to eat here?', 'sanitation'),
    ('Are there any discounts going on?', 'offers'),
    ('Can I see the vegan option?', 'vegan_enquiry'),
    ('Can I see the vegetarian options?', 'veg_enquiry'),
    ('Could you tell me more about recipe of this dish?', 'recipe_enquiry'),
    ('what do you recommend?', 'suggest'),
    ('okay', 'general')
]

passed = 0
total = len(test_cases)

for message, expected_intent in test_cases:
    try:
        response = requests.post(f'{base_url}/api/chatbot',
                               json={'message': message},
                               timeout=5)
        if response.status_code == 200:
            data = response.json()
            actual_intent = data.get('intent')
            status = '✅' if actual_intent == expected_intent else '❌'
            print(f'{status} "{message}" -> Expected: {expected_intent}, Got: {actual_intent}')
            if actual_intent == expected_intent:
                passed += 1
        else:
            print(f'❌ "{message}" -> HTTP {response.status_code}')
    except Exception as e:
        print(f'❌ "{message}" -> ERROR: {e}')
    time.sleep(0.1)  # Small delay to avoid overwhelming the server

print(f'\n📊 Test Results: {passed}/{total} passed ({passed/total*100:.1f}%)')
print('✅ Intent matching testing completed!')
