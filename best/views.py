from django.shortcuts import render, get_object_or_404
from django.http import HttpResponse, Http404
from models import *
import json

def lat_lng_for_stop(request):
    name = request.GET.get('name', None)
    if not name:
        return HttpResponse("Please provide a 'name' GET param")
    matched_stops = Stop.objects.filter(stop_name__iexact=name)
    if not matched_stops.exists():
        raise Http404("No stop found with that name")
    stop = matched_stops[0]
    stop_dict = {
        'lat': stop.stop_lat,
        'lon': stop.stop_lon
    }
    return HttpResponse(json.dumps(stop_dict))