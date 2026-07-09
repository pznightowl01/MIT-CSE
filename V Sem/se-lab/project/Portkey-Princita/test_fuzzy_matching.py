import requests
import time

base_url = 'http://127.0.0.1:5000'

print('🔍 Testing Fuzzy Matching for Failed Cases')
print('=' * 40)

# Test cases that failed in previous test
test_cases = [
    ('what is the location?', 'address'),
    ('is it really safe to eat here?', 'sanitation'),
    ('Could you tell me more about recipe of this dish?', 'recipe_enquiry'),
    ('what do you recommend?', 'suggest'),
    # Additional variations to test fuzzy matching
    ('where is the restaurant', 'address'),
    ('safety protocols', 'sanitation'),
    ('tell me the recipe', 'recipe_enquiry'),
    ('recommend me something', 'suggest')
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
    time.sleep(0.1)

print(f'\n📊 Fuzzy Test Results: {passed}/{total} passed ({passed/total*100:.1f}%)')
print('✅ Fuzzy matching testing completed!')
