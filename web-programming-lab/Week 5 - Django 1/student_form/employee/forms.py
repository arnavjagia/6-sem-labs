from django import forms

class PromotionForm(forms.Form):
    # Providing options directly for employee_id instead of fetching from the model
    EMPLOYEE_CHOICES = [
        ('1', 'Employee 1'),
        ('2', 'Employee 2'),
        ('3', 'Employee 3'),
        ('4', 'Employee 4'),
        ('5', 'Employee 5'),
        # Add more employee options here
    ]
    
    employee_id = forms.ChoiceField(choices=EMPLOYEE_CHOICES, label="Employee ID")
    date_of_joining = forms.DateField(label="Date of Joining", widget=forms.DateInput(attrs={'type': 'date'}))
