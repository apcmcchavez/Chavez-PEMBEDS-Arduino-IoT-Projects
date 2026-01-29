from django.db import models

class Detection(models.Model):
    sensor_type = models.CharField(max_length=50, default='ultrasonic')
    distance = models.IntegerField()  # Distance in cm
    timestamp = models.DateTimeField(auto_now_add=True)
    
    class Meta:
        ordering = ['-timestamp']  # Newest first
    
    def __str__(self):
        return f"Detection #{self.id} - {self.distance}cm at {self.timestamp}"