import xml.etree.ElementTree as ET
import urllib2
import json

def get_message(otp_url):

	url = urllib2.urlopen(otp_url)
	r=json.loads(url.read())
	'''
	tree = ET.parse('url.read()')
	root = tree.getroot()

	x=root.find('plan').find('itineraries')
	print(x)

	for i in x.findall('itineraries'):
		legs=i.find('legs')
		for l in legs:
			if l.find('mode').text == "BUS":
				f=l.find('from')
				t=l.find('to')
				print("take bus " + f.find('stopId').find('id').text +"from: " + (f.find('name').text))
				print("to: " + t.find('name').text)

		print("**** next ****\n\n")		
	'''
	p=r['plan']['itineraries']
	ret = ""
	q = p[0]

	legs= q['legs']
	for l in legs:
		if l['mode'] == "BUS":
			f=l['from']
			#print(f)
			t=l['to']
			print("take bus " + f['stopId'] +"\nfrom: " + f['name'])
			ret = ret + "take bus " + f['stopId'] +"\nfrom: " + f['name']
			ret = ret + "to: " + t['name']+"\n"
			print("to: " + t['name']+"\n")
			
	return ret
