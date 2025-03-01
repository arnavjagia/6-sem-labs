# calculator/views.py
from django.shortcuts import render

def calculator(request):
    context = {}
    
    if request.method == 'POST':
        num1 = request.POST.get('num1')
        num2 = request.POST.get('num2')
        operation = request.POST.get('operation')
        
        try:
            num1 = int(num1)
            num2 = int(num2)
            
            if operation == 'add':
                result = num1 + num2
                operation_symbol = '+'
            elif operation == 'subtract':
                result = num1 - num2
                operation_symbol = '-'
            elif operation == 'multiply':
                result = num1 * num2
                operation_symbol = '×'
            elif operation == 'divide':
                if num2 == 0:
                    result = "Error: Division by zero!"
                    operation_symbol = '÷'
                else:
                    result = num1 / num2
                    operation_symbol = '÷'
            else:
                result = "Invalid operation"
                operation_symbol = '?'
            
            context = {
                'num1': num1,
                'num2': num2,
                'operation': operation,
                'result': result,
                'operation_symbol': operation_symbol,
            }
        except ValueError:
            context = {
                'num1': num1,
                'num2': num2,
                'operation': operation,
                'result': "Please enter valid integers!"
            }
    
    return render(request, 'calculator/index.html', context)