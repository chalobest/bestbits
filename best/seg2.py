from fuzzywuzzy import fuzz,process
import re
from string import replace
from os.path import join
from django.conf import settings

def get_lists():
	'''opening the file with bus stop names'''
	f1=open(join(settings.DATA_DIR, "bus_stop_no_re_s.txt"))
	bus_stops=f1.readlines()
	f1.close()

	

	'''removing \n from the names'''
	for i in range(len(bus_stops)):
		t=""
		for ch in bus_stops[i]:
			if ch!='\n':
				t=t+ch
		bus_stops[i]=t

	

	return bus_stops

'''
inp=raw_input('input: ')
inp=inp+' ' 
#inp=filter(lambda x: x.isalnum() or x=='\n' or x.isdigit() or x==' ',inp)
inp=inp.lower()
print inp0
'''

''' input: none
	output: returns lists of various types of bus bus_stops
	'''
def remove_red(l):
	nl=[]
	for i in l:
		if i not in nl:
			nl.append(i)
	return nl

def get_seg_lists():
	bus_stops=get_lists()
	
	#st_ln : station list
	st_lt=[]
	st=['station',' stn',' st']
	for bs in bus_stops:
		inp=bs.lower()
		for i in st:	
		#	print fuzz.partial_ratio(i,inp)
			if fuzz.partial_ratio(i,inp) > 80:
				pi= replace(inp,'stn.','')
				if pi==inp:
					pi= replace(inp,'stn','')
				pi=replace(pi,'.',' ')
				st_lt.append([bs,pi])
	st_lt=remove_red(st_lt)


	#bs_lt:  bus list
	bs_lt=[]
	bus=[' bus','bs']
	for bs in bus_stops:
		inp=bs.lower()
		for i in bus:	
			if fuzz.partial_ratio(i,inp) > 80:
				pi=replace(inp,'bus ','')
				pi=replace(pi,'.',' ')
				bs_lt.append([bs,pi])
	bs_lt=remove_red(bs_lt)
	#print '\n',bs_lt

	#et_ln: east list
	et_lt=[]
	et=['east','(e)','-e',' e ']
	for bs in bus_stops:
		inp=bs.lower()
		for i in et:
			if fuzz.partial_ratio(i,inp) > 75:
				pi=replace(inp,'(e)','')
				pi=replace(pi,'-e','')
				pi=replace(pi,'( e )','')
				pi=replace(pi,'- e','')
				pi=replace(pi,' east','')
				pi=replace(pi,'.',' ')
				et_lt.append([bs,pi])
	et_lt=remove_red(et_lt)

#	print "\neast: ",et_lt

	#wt_ln : west list
	wt_lt=[]
	wt=['west','(w)','-w',' w ']
	for bs in bus_stops:
		inp=bs.lower()
		for i in wt:
			if fuzz.partial_ratio(i,inp) > 75:
				pi=replace(inp,'(w)','')
				pi=replace(pi,'-w','')
				pi=replace(pi,'( w )','')
				pi=replace(pi,'- w','')
				pi=replace(pi,'.',' ')
				wt_lt.append([bs,pi])
	wt_lt=remove_red(wt_lt)
#	print "\nwest: ",wt_lt

	#ng_ln : nagar list
	ng_lt=[]
	ng=['nagar','ngr']
	for bs in bus_stops:
		inp=bs.lower()
		for i in ng:
			if fuzz.partial_ratio(i,inp) > 75:
				pi=replace(inp,' ngr.','')
				pi=replace(pi,' nagar','')
				pi=replace(pi,'.',' ')
				ng_lt.append([bs,pi])
	ng_lt=remove_red(ng_lt)
#	print "\nnagars: ",ng_lt

	#pk_ln: park list
	pk_lt=[]
	pk=[' park',' prk']
	for bs in bus_stops:
		inp=bs.lower()
		for i in pk:
			if fuzz.partial_ratio(i,inp) > 80:
				pi=replace(inp,'park','')
				pi=replace(pi,'.',' ')
				pk_lt.append([bs,pi])
	pk_lt=remove_red(pk_lt)

	#print "\nparks: ",pk_lt

	#mg_ln : marg list
	mg_lt=[]
	mg=[' marg',' rd',' road']
	for bs in bus_stops:
		inp=bs.lower()
		for i in mg:
			if fuzz.partial_ratio(i,inp) > 80:
				pi=replace(inp,' rd.',' ')
				pi=replace(pi,' marg','')
				pi=replace(pi,' rd','')
				pi=replace(pi,' road','' )
				pi=replace(pi,'.',' ')
				mg_lt.append([bs,pi])
	mg_lt=remove_red(mg_lt)

	#print "\nmargs: ",mg_lt

	#dp_lt= depot list
	dp_lt=[]
	dp=[' depot',' dpt']
	for bs in bus_stops:
		inp=bs.lower()
		for i in dp:
			if fuzz.partial_ratio(i,inp) > 80:
				pi=replace(inp,'depot','')
				pi=replace(pi,'.',' ')
				dp_lt.append([bs,pi])
	dp_lt=remove_red(dp_lt)

	#print "\ndepots: ",dp_lt
#	ud_lt= udaan list
	ud_lt=[]
	ud=[' udaan',' udn']
	for bs in bus_stops:
		inp=bs.lower()
		for i in ud:
			if fuzz.partial_ratio(i,inp) > 80:
				pi=replace(inp,'udn.','')
				pi=replace(pi,'.',' ')
				ud_lt.append([bs,pi])
	ud_lt=remove_red(ud_lt)

	#print "\nudaans: ",ud_lt

	#ck_lt=chowks
	ck_lt=[]
	ck=[' chowk',' chk']
	for bs in bus_stops:
		inp=bs.lower()
		for i in ck:
			if fuzz.partial_ratio(i,inp) > 80:
				pi=replace(inp,'chk.','')
				pi=replace(pi,'.',' ')
				ck_lt.append([bs,pi])
	ck_lt=remove_red(ck_lt)

	#print "\nchowks: ",ck_lt

	#vg_lt=villages
	vg_lt=[]
	vg=[' village',' vlg']
	for bs in bus_stops:
		inp=bs.lower()
		for i in vg:
			if fuzz.partial_ratio(i,inp) > 80:
				pi=replace(inp,'village','')
				pi=replace(pi,'.',' ')
				vg_lt.append([bs,pi])
	vg_lt=remove_red(vg_lt)

	#print "\nvillagess: ",vg_lt

	#tr_lt=terminus
	tr_lt=[]
	tr=[' terminus',' trmns']
	for bs in bus_stops:
		inp=bs.lower()
		for i in tr:
			if fuzz.partial_ratio(i,inp) > 80:
				pi=replace(inp,'terminus','')
				pi=replace(pi,'.',' ')
				tr_lt.append([bs,pi])
	tr_lt=remove_red(tr_lt)
#	print "\nterminus: ",tr_lt

	#ext_lt: extension
	ext_lt=[]
	ext=[' extension','extn','ext']
	for bs in bus_stops:
		inp=bs.lower()
		for i in ext:
			if fuzz.partial_ratio(i,inp) > 80:
				pi=replace(inp,'extn.','')
				pi=replace(pi,'ext.','')
				pi=replace(pi,'.',' ')
				ext_lt.append([bs,pi])
	ext_lt=remove_red(ext_lt)

	#print "\nextensions: ",mg_lt

	#cly_lt: colony
	cly_lt=[]
	cly=[' colony',' cly']
	for bs in bus_stops:
		inp=bs.lower()
		for i in cly:
			if fuzz.partial_ratio(i,inp) > 80:
				pi=replace(inp,'cly.','')
				pi=replace(pi,'.',' ')
				cly_lt.append([bs,pi])
	cly_lt=remove_red(cly_lt)

	#print "\ncolonys: ",cly_lt

	#pd_lt=pada
	pd_lt=[]
	pd=[' pada']
	for bs in bus_stops:
		inp=bs.lower()
		for i in pd:
			if fuzz.partial_ratio(i,inp) > 80:
				pi=replace(inp,' pada','')
				pi=replace(pi,'.',' ')
				pd_lt.append([bs,pi])
	pd_lt=remove_red(pd_lt)

	#print "\npada: ",pd_lt
	
	#bs_lt:  bus list
	gn_lt=[]
	gn=[' garden','grdn']
	for bs in bus_stops:
		inp=bs.lower()
		for i in gn:	
			if fuzz.partial_ratio(i,inp) > 80:
				pi=replace(inp,' garden','')
				pi=replace(pi,'.',' ')
				gn_lt.append([bs,pi])
	gn_lt=remove_red(gn_lt)
	#print '\n',bs_lt

	return bus_stops,st_lt,bs_lt,et_lt,wt_lt,ng_lt,pk_lt,mg_lt,dp_lt,ud_lt,ck_lt,vg_lt,tr_lt,ext_lt,cly_lt,pd_lt,gn_lt



'''
in parks check for MANTRI PARK/SHIVSHAHI PRAKALP case
'''


###addition of 'east' in cases to replace
