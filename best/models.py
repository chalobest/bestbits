# This is an auto-generated Django model module.
# You'll have to do the following manually to clean this up:
#   * Rearrange models' order
#   * Make sure each model has one field with primary_key=True
#   * Remove `managed = True` lines if you wish to allow Django to create, modify, and delete the table
# Feel free to rename the models, but don't rename db_table values or field names.
#
# Also note: You'll have to insert the output of 'django-admin sqlcustom [app_label]'
# into your database.
from __future__ import unicode_literals

from django.db import models


class AreaMaster(models.Model):
    area_code = models.IntegerField(primary_key=True)
    area_name = models.CharField(max_length=1024, blank=True, null=True)

    def __unicode__(self):
        return self.area_name

    class Meta:
        managed = True
        verbose_name = "Area"
        verbose_name_plural = "Areas"
        db_table = 'area_master'


class RoadMaster(models.Model):
    road_code = models.IntegerField(primary_key=True)
    road_name = models.CharField(max_length=1024, blank=True, null=True)

    def __unicode__(self):
        return self.road_name

    class Meta:
        managed = True
        db_table = 'road_master'
        verbose_name = "Road"
        verbose_name_plural = "Roads"


class RouteAtlas(models.Model):
    route_no = models.CharField(max_length=1024, blank=True, null=True)
    depot = models.CharField(max_length=1024, blank=True, null=True)
    froms = models.CharField(max_length=1024, blank=True, null=True)
    first = models.CharField(max_length=1024, blank=True, null=True)
    last = models.CharField(max_length=1024, blank=True, null=True)
    tos = models.CharField(max_length=1024, blank=True, null=True)
    firstb = models.CharField(max_length=1024, blank=True, null=True)
    lastb = models.CharField(max_length=1024, blank=True, null=True)
    span = models.FloatField(blank=True, null=True)
    r2 = models.IntegerField(blank=True, null=True)
    r3 = models.IntegerField(blank=True, null=True)
    r4 = models.IntegerField(blank=True, null=True)
    r5 = models.IntegerField(blank=True, null=True)
    h1 = models.IntegerField(blank=True, null=True)
    h2 = models.IntegerField(blank=True, null=True)
    h3 = models.IntegerField(blank=True, null=True)
    h4 = models.IntegerField(blank=True, null=True)
    h5 = models.IntegerField(blank=True, null=True)
    shtype = models.CharField(max_length=1024, blank=True, null=True)
    id = models.IntegerField(primary_key=True)
    route = models.ForeignKey("RouteMaster")

    def __unicode__(self):
        return self.route_no

    class Meta:
        managed = True
        db_table = 'route_atlas'


class RouteDet(models.Model):
    id = models.AutoField(primary_key=True)
    route = models.ForeignKey("RouteMaster")
    stopsr = models.IntegerField(blank=True, null=True)
    stopcd = models.ForeignKey("StopMaster")
    stage = models.IntegerField(blank=True, null=True)
    km = models.FloatField(blank=True, null=True)

    def __unicode__(self):
        return str(self.route_id)

    class Meta:
        managed = True
        db_table = 'route_det'


class RouteMaster(models.Model):
    route_id = models.IntegerField(primary_key=True)
    route_al = models.CharField(max_length=1024, blank=True, null=True)
    froms = models.CharField(max_length=1024, blank=True, null=True)
    tos = models.CharField(max_length=1024, blank=True, null=True)
    span = models.DecimalField(max_digits=65535, decimal_places=65535, blank=True, null=True)
    stages = models.IntegerField(blank=True, null=True)

    def __unicode__(self):
        return str(self.route_id)

    class Meta:
        managed = True
        db_table = 'route_master'


class StopMaster(models.Model):
    stop_id = models.DecimalField(primary_key=True, max_digits=65535, decimal_places=65535)
    stop_name = models.CharField(max_length=1024, blank=True, null=True)
    stop_fl = models.CharField(max_length=1024, blank=True, null=True)
    road = models.ForeignKey("RoadMaster")
    area = models.ForeignKey("AreaMaster")

    def __unicode__(self):
        return self.stop_name

    class Meta:
        managed = True
        db_table = 'stop_master'


class Stop(models.Model):
    stop = models.ForeignKey("StopMaster", primary_key=True)
    stop_name = models.CharField(max_length=1024, blank=True, null=True)
    stop_lat = models.FloatField(blank=True, null=True)
    stop_lon = models.FloatField(blank=True, null=True)

    def __unicode__(self):
        return self.stop_name

    class Meta:
        managed = True
        db_table = 'stops'
