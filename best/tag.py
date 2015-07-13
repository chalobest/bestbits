from fuzzywuzzy import fuzz,process
import re

def find_tag(s,list,thrd):
	inp=s.lower()
	for i in list:	
		if fuzz.ratio(i,s) >= thrd:
			return 1
	return 0

def get_tag_list(s):	
	catg =[	['station',80,0],
			['bus',80,0],
			['east',80,0],
			['west',80,0],
			#['nagar',80,0],
			['park',80,0],
			['marg',80,0],
			['depot',75,0],
			['udaan',80,0],
			['chowk',80,0],
			['village',80,0],
			['terminus',80,0],
			['extension',80,0],
			['colony',80,0],
			['pada',80,0],
			['garden',80,0]]

	station=['station',' stn',' st',' stat']
	bus=[' bus','bs']
	east=['east','(e)','-e',' e ']
	west=['west','(w)','-w',' w ']
	#nagar=['nagar','ngr']
	park=[' park',' prk']
	marg=[' marg',' rd',' road']
	depot=[' depot',' dpt']
	udaan=[' udaan',' udn']
	chowk=[' chowk',' chk']
	village=[' village',' vlg']
	terminus=[' terminus',' trmns']
	extension=[' extension',' extn']
	colony=[' colony',' cly']
	pada= ['pada']	
	garden=['garden','grdn']
	for i in range(len(catg)):
		catg[i][2]=find_tag(s,eval(catg[i][0]),catg[i][1])

	nl=[]
	for t in range(len(catg)):
		if catg[t][2]==1:
			nl.append(catg[t][0])

	return nl

#print get_tag_list('dept')


#use of spaces before the matching string?
#threshold value of partial ratio = 75 for depot
#milenium business park in bus list 
#use order while matching strings


#change1 : use absolute ratio to find tags...
#change2:  ask rajat to remove the tags as in tag2.py
#change3: addition of road to margs in seg2 and tag.py
