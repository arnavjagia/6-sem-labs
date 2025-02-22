from django.shortcuts import render
from django.http import HttpResponse

def index(request):
    if request.method == 'POST':
        name = request.POST.get('name')
        dob = request.POST.get('dob')
        address = request.POST.get('address')
        contact_number = request.POST.get('contact_number')
        email_id = request.POST.get('email_id')
        english_marks = int(request.POST.get('english_marks', 0))
        physics_marks = int(request.POST.get('physics_marks', 0))
        chemistry_marks = int(request.POST.get('chemistry_marks', 0))

        total_marks = english_marks + physics_marks + chemistry_marks
        percentage = (total_marks / 300) * 100  # Assuming each subject is out of 100

        context = {
            'message': f"Total Percentage: {percentage:.2f}%",
            'name': name,
            'dob': dob,
            'address': address,
            'contact_number': contact_number,
            'email_id': email_id,
            'english_marks': english_marks,
            'physics_marks': physics_marks,
            'chemistry_marks': chemistry_marks,
        }
        return render(request, 'webapp/index.html', context)

    return render(request, 'webapp/index.html')
