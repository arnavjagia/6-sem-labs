from django.shortcuts import render, redirect
from .forms import CarForm

def car_form_view(request):
    if request.method == 'POST':
        form = CarForm(request.POST)
        if form.is_valid():
            # Get the form data
            manufacturer = form.cleaned_data['manufacturer']
            model = form.cleaned_data['model']
            
            # Redirect to the result page with parameters
            return redirect('car_result', manufacturer=manufacturer, model=model)
    else:
        form = CarForm()
    
    return render(request, 'carinfo/index.html', {'form': form})

def car_result_view(request, manufacturer, model):
    # Get manufacturer display name
    manufacturer_display = dict(CarForm.MANUFACTURER_CHOICES).get(manufacturer, manufacturer)
    
    context = {
        'manufacturer': manufacturer_display,
        'model': model
    }
    return render(request, 'carinfo/car_result.html', context)