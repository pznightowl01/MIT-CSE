import requests
import time

base_url = 'http://127.0.0.1:5000'

print('🔍 Testing Concise Responses')
print('=' * 30)

# Test concise responses for various intents
test_cases = [
    ('Hi', 'Should be concise greeting'),
    ('Book a table', 'Should be concise booking response'),
    ('Available seats', 'Should be concise availability response'),
    ('Goodbye', 'Should be concise goodbye'),
    ('what is your name', 'Should be concise identity response'),
    ('when are you guys open', 'Should be concise hours response'),
    ('whats on the menu', 'Should be concise menu response'),
    ('contact information', 'Should be concise contact response'),
    ('what is the location?', 'Should be concise address response'),
    ('the noodles were amazing', 'Should be concise positive feedback response'),
    ('too salty', 'Should be concise negative feedback response'),
    ('is it really safe to eat here?', 'Should be concise sanitation response'),
    ('Are there any discounts going on?', 'Should be concise offers response'),
    ('Can I see the vegan option?', 'Should be concise vegan response'),
    ('Can I see the vegetarian options?', 'Should be concise veg response'),
    ('Could you tell me more about recipe of this dish?', 'Should be concise recipe response'),
    ('what do you recommend?', 'Should be concise suggest response'),
    ('okay', 'Should be concise general response')
]

print('Testing response lengths and content:')
print('-' * 50)

for message, description in test_cases:
    try:
        response = requests.post(f'{base_url}/api/chatbot',
                               json={'message': message},
                               timeout=5)
        if response.status_code == 200:
            data = response.json()
            bot_response = data.get('response', '')
            intent = data.get('intent', 'unknown')
            response_length = len(bot_response)

            # Check if response is reasonably concise (under 200 chars for concise intents)
            is_concise = response_length < 200
            status = '✅' if is_concise else '⚠️'

            print(f'{status} {intent}: {response_length} chars - {description}')
            if not is_concise:
                print(f'   Response: {bot_response[:100]}...')
        else:
            print(f'❌ HTTP {response.status_code} for \"{message}\"')
    except Exception as e:
        print(f'❌ ERROR for \"{message}\": {e}')
    time.sleep(0.1)

print('\n✅ Concise response testing completed!')
