import requests
import time

base_url = 'http://127.0.0.1:5000'

print('🔍 Testing Order and Payment Queries')
print('=' * 40)

# Test cases for order and payment queries
test_cases = [
    ('How do I place an order?', 'order_help'),
    ('What payment methods do you accept?', 'payment_info'),
    ('How do I order food?', 'order_help'),
    ('How can I pay?', 'payment_info'),
    ('Tell me how to order', 'order_help'),
    ('What are your payment options?', 'payment_info')
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

print(f'\n📊 Order/Payment Test Results: {passed}/{total} passed ({passed/total*100:.1f}%)')
print('✅ Order and payment testing completed!')
