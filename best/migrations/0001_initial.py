# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='AreaMaster',
            fields=[
                ('area_code', models.IntegerField(serialize=False, primary_key=True)),
                ('area_name', models.CharField(max_length=1024, null=True, blank=True)),
            ],
            options={
                'db_table': 'area_master',
                'managed': True,
            },
        ),
        migrations.CreateModel(
            name='RoadMaster',
            fields=[
                ('road_code', models.IntegerField(serialize=False, primary_key=True)),
                ('road_name', models.CharField(max_length=1024, null=True, blank=True)),
            ],
            options={
                'db_table': 'road_master',
                'managed': True,
            },
        ),
        migrations.CreateModel(
            name='RouteAtlas',
            fields=[
                ('route_no', models.CharField(max_length=1024, null=True, blank=True)),
                ('depot', models.CharField(max_length=1024, null=True, blank=True)),
                ('froms', models.CharField(max_length=1024, null=True, blank=True)),
                ('first', models.CharField(max_length=1024, null=True, blank=True)),
                ('last', models.CharField(max_length=1024, null=True, blank=True)),
                ('tos', models.CharField(max_length=1024, null=True, blank=True)),
                ('firstb', models.CharField(max_length=1024, null=True, blank=True)),
                ('lastb', models.CharField(max_length=1024, null=True, blank=True)),
                ('span', models.FloatField(null=True, blank=True)),
                ('r2', models.IntegerField(null=True, blank=True)),
                ('r3', models.IntegerField(null=True, blank=True)),
                ('r4', models.IntegerField(null=True, blank=True)),
                ('r5', models.IntegerField(null=True, blank=True)),
                ('h1', models.IntegerField(null=True, blank=True)),
                ('h2', models.IntegerField(null=True, blank=True)),
                ('h3', models.IntegerField(null=True, blank=True)),
                ('h4', models.IntegerField(null=True, blank=True)),
                ('h5', models.IntegerField(null=True, blank=True)),
                ('shtype', models.CharField(max_length=1024, null=True, blank=True)),
                ('id', models.IntegerField(serialize=False, primary_key=True)),
            ],
            options={
                'db_table': 'route_atlas',
                'managed': True,
            },
        ),
        migrations.CreateModel(
            name='RouteDet',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('stopsr', models.IntegerField(null=True, blank=True)),
                ('stage', models.IntegerField(null=True, blank=True)),
                ('km', models.FloatField(null=True, blank=True)),
            ],
            options={
                'db_table': 'route_det',
                'managed': True,
            },
        ),
        migrations.CreateModel(
            name='RouteMaster',
            fields=[
                ('route_id', models.IntegerField(serialize=False, primary_key=True)),
                ('route_al', models.CharField(max_length=1024, null=True, blank=True)),
                ('froms', models.CharField(max_length=1024, null=True, blank=True)),
                ('tos', models.CharField(max_length=1024, null=True, blank=True)),
                ('span', models.DecimalField(null=True, max_digits=65535, decimal_places=65535, blank=True)),
                ('stages', models.IntegerField(null=True, blank=True)),
            ],
            options={
                'db_table': 'route_master',
                'managed': True,
            },
        ),
        migrations.CreateModel(
            name='StopMaster',
            fields=[
                ('stop_id', models.DecimalField(serialize=False, primary_key=True, decimal_places=65535, max_digits=65535)),
                ('stop_name', models.CharField(max_length=1024, null=True, blank=True)),
                ('stop_fl', models.CharField(max_length=1024, null=True, blank=True)),
            ],
            options={
                'db_table': 'stop_master',
                'managed': True,
            },
        ),
        migrations.CreateModel(
            name='Stop',
            fields=[
                ('stop_id', models.ForeignKey(primary_key=True, serialize=False, to='best.StopMaster')),
                ('stop_name', models.CharField(max_length=1024, null=True, blank=True)),
                ('stop_lat', models.FloatField(null=True, blank=True)),
                ('stop_lon', models.FloatField(null=True, blank=True)),
            ],
            options={
                'db_table': 'stops',
                'managed': True,
            },
        ),
        migrations.AddField(
            model_name='stopmaster',
            name='area_id',
            field=models.ForeignKey(to='best.AreaMaster'),
        ),
        migrations.AddField(
            model_name='stopmaster',
            name='road_id',
            field=models.ForeignKey(to='best.RoadMaster'),
        ),
        migrations.AddField(
            model_name='routedet',
            name='route_id',
            field=models.ForeignKey(to='best.RouteMaster'),
        ),
        migrations.AddField(
            model_name='routedet',
            name='stopcd',
            field=models.ForeignKey(to='best.StopMaster'),
        ),
        migrations.AddField(
            model_name='routeatlas',
            name='route_id',
            field=models.ForeignKey(to='best.RouteMaster'),
        ),
    ]
