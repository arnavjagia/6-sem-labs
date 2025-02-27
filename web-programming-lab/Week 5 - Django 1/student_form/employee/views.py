from django.shortcuts import render
from .forms import PromotionForm
from django.utils import timezone
import datetime

def check_eligibility(request):
    eligible = None  # Initialize eligible
    if request.method == 'POST':
        form = PromotionForm(request.POST)
        if form.is_valid():
            employee_id = form.cleaned_data['employee_id']
            date_of_joining = form.cleaned_data['date_of_joining']
            today = timezone.now().date()  # Use timezone-aware date
            experience = today.year - date_of_joining.year - ((today.month, today.day) < (date_of_joining.month, date_of_joining.day)) # calculates difference in years.

            if experience > 5:
                eligible = "YES"
            else:
                eligible = "NO"
    else:
        form = PromotionForm()

    return render(request, 'employee/eligibility.html', {'form': form, 'eligible': eligible})
