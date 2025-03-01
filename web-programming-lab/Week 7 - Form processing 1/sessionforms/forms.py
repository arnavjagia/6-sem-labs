from django import forms

class UserForm(forms.Form):
    name = forms.CharField(label='Name', max_length=100)
    roll = forms.CharField(label='Roll', max_length=50)
    subjects = forms.ChoiceField(
        label='Subjects',
        choices=[
            ('math', 'Mathematics'),
            ('sci', 'Science'),
            ('eng', 'English'),
            ('hist', 'History'),
            ('cs', 'Computer Science')
        ]
    )
