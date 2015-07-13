from django.shortcuts import render, get_object_or_404
from django.http import HttpResponse, Http404
from models import *
import json
from twi_module_copy import final
from parse_xml import get_message
import datetime
import urllib

def lat_lng_for_stop(request):
    name = request.GET.get('name', None)
    if not name:
        return HttpResponse("Please provide a 'name' GET param")
    lat, lon = get_lat_lng(name)
    stop_dict = {
        'lat': lat,
        'lon': lon
    }
    return HttpResponse(json.dumps(stop_dict))

def messaging(request):
    message = request.GET.get("msg", None)
    if not message:
        return HttpResponse("Please provide a 'msg' GET param")
    source, destination = final(message)
    source_lat, source_lon = get_lat_lng(source)
    dest_lat, dest_lon = get_lat_lng(destination)
    now = datetime.datetime.now()
    time = now.strftime("%-I:%M%p").lower()
    date = now.strftime("%m-%d-%Y")
    otp_params = {
        'fromPlace': "%f,%f" % (source_lat, source_lon,),
        'toPlace': "%f,%f" % (dest_lat, dest_lon,),
        'time': time,
        'date': date,
        'mode': 'TRANSIT,WALK',
        'maxWalkDistance': 804.672
    }
    url_params = urllib.urlencode(otp_params)
    otp_url = "http://trip.chalobest.in/otp/routers/default/plan?%s" % url_params
    response = get_message(otp_url)
    return HttpResponse(response)

def get_lat_lng(stop_name):
    matched_stops = Stop.objects.filter(stop_name__iexact=stop_name)
    if not matched_stops.exists():
        raise Http404("No stop found with that name")
    stop = matched_stops[0]
    return (stop.stop_lat, stop.stop_lon,)
