from django.db import models

class Employee(models.Model):
    employee_id = models.CharField(max_length=50, unique=True)  # Example: Could also be an AutoField or IntegerField
    # other fields like name, etc.
    def __str__(self):
        return self.employee_id
