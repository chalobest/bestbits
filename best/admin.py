from django.contrib import admin
from models import *

class AreaAdmin(admin.ModelAdmin):
    search_fields = ('area_name',)

admin.site.register(AreaMaster, AreaAdmin)
admin.site.register(RoadMaster)
admin.site.register(RouteAtlas)
admin.site.register(RouteDet)
admin.site.register(Stop)

