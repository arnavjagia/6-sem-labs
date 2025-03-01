from django import forms

class CarForm(forms.Form):
    MANUFACTURER_CHOICES = [
        ('toyota', 'Toyota'),
        ('honda', 'Honda'),
        ('ford', 'Ford'),
        ('bmw', 'BMW'),
        ('mercedes', 'Mercedes'),
        ('volkswagen', 'Volkswagen'),
        ('audi', 'Audi'),
    ]
    
    manufacturer = forms.ChoiceField(choices=MANUFACTURER_CHOICES)
    model = forms.CharField(max_length=100)