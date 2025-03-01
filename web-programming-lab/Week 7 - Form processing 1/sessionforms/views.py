from django.shortcuts import render, redirect
from .forms import UserForm

def first_page(request):
    form = UserForm()
    
    # handle post req
    if request.method == 'POST':
        form = UserForm(request.POST)
        if form.is_valid():
            # Store in session
            request.session['user_data'] = {
                'name': form.cleaned_data['name'],
                'roll': form.cleaned_data['roll'],
                'subject': dict(form.fields['subjects'].choices).get(form.cleaned_data['subjects'])
            }
            return redirect('second_page')
    
    return render(request, 'sessionforms/firstPage.html', {'form': form})

def second_page(request):
    user_data = request.session.get('user_data', {})

    return render(request, 'sessionforms/secondPage.html', {'user_data': user_data})