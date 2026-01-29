from django.contrib import admin
from .models import Detection

@admin.register(Detection)
class DetectionAdmin(admin.ModelAdmin):
    # This controls what columns you see in the list
    list_display = ('id', 'sensor_type', 'distance', 'timestamp')
    
    # This lets you filter by date on the right side
    list_filter = ('timestamp', 'sensor_type')
    
    # This makes the ID clickable to edit the record
    list_display_links = ('id',)
    
    # This adds a search bar for the ID
    search_fields = ('id',)