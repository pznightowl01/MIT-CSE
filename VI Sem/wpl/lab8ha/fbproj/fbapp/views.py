from django.shortcuts import render
from .forms import FeedbackForm

def feedback_view(request):
  form = FeedbackForm()
  message = None
  if request.method == 'POST':
    
    form = FeedbackForm(request.POST)
    if form.is_valid():
      student_name = form.cleaned_data['student_name"
      message = f"Thank You {student_name}, for your feedback."
      form = FeedbackForm() # Reset form
  return render (request, 'fbapp/feedback.html', {'form': form, 'message': message})
