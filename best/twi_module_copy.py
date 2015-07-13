from fuzzywuzzy import fuzz,utils,StringMatcher

from seg2 import get_seg_lists
from tag import get_tag_list
from nltk.util import ngrams
import re
import nltk
from string import replace
from datetime import datetime
import sys
try:
    from fuzzywuzzy.StringMatcher import StringMatcher as SequenceMatcher
except ImportError:
    warnings.warn('Using slow pure-python SequenceMatcher. Install python-Levenshtein to remove this warning')
    from difflib import SequenceMatcher
from django.conf import settings
from os.path import join

bus_stops,station,bus,east,west,nagar,park,marg,depot,udaan,chowk,village,terminus,extension,colony,pada,garden=get_seg_lists()

#bus_no contains all the bus no(routes)
f1=open(join(settings.DATA_DIR, "bus_no.txt"))			
bus_no=f1.readlines()

#removing \n
for i in range(len(bus_no)):
		t=""
		for ch in bus_no[i]:
			if ch!='\n':
				t=t+ch
		bus_no[i]=t
f1.close()

store_ratio=29				#default value of stored ratio
store_last_added=''				#default value of last checked stop
store_bus=''

#bus_no,bus_stops,station,bus,east,west,nagar,park,marg,depot,udaan,chowk,village,terminus,extension,colony,pada,garden='','','','','','','','','','','','','','','','','',''


def partial_ratio2(s1, s2):
    """"Return the ratio of the most similar substring
    as a number between 0 and 100."""

    if s1 is None:
        raise TypeError("s1 is None")
    if s2 is None:
        raise TypeError("s2 is None")
    s1, s2 = utils.make_type_consistent(s1, s2)
    if len(s1) == 0 or len(s2) == 0:
        return 0

    
    shorter = s1
    longer = s2


    m = SequenceMatcher(None, shorter, longer)
    blocks = m.get_matching_blocks()

    # each block represents a sequence of matching characters in a string
    # of the form (idx_1, idx_2, len)
    # the best partial match will block align with at least one of those blocks
    #   e.g. shorter = "abcd", longer = XXXbcdeEEE
    #   block = (1,3,3)
    #   best score === ratio("abcd", "Xbcd")
    scores = []
    for block in blocks:
        long_start = block[1] - block[0] if (block[1] - block[0]) > 0 else 0
        long_end = long_start + len(shorter)
        long_substr = longer[long_start:long_end]

        m2 = SequenceMatcher(None, shorter, long_substr)
        r = m2.ratio()
        if r > .995:
            return 100
        else:
            scores.append(r)

    return int(100 * max(scores))




#query when there are two stations
def query1(s,bus_st):
	tl=0
	token=nltk.word_tokenize(s)
	for i in range(len(token)):
		if token[i].lower()=='to' or token[i]=='2':
			tl=i
	dest_i= tl+1
	temp=token[dest_i:]
	temp=' '.join(temp[:3])
	 
	if fuzz.ratio(temp.lower(),bus_st[0].lower()) > fuzz.ratio(temp.lower(),bus_st[1].lower()):
		dest = bus_st[0]
		source = bus_st[1]
	else:
		dest = bus_st[1]
		source = bus_st[0]
	return [source,dest]

#query when there is only one station
def query2(s,bus_st):
	return [bus_st[0]]





#this is used when there are tags
def match_in_list(l,st):
	global store_ratio
	global store_last_added	

	h=[]
	for x in l:
		if fuzz.token_set_ratio(x[1],st) >= 75 and fuzz.partial_ratio(x[1],st) > 75 and fuzz.ratio(x[1],st)>29:
				h.append(x[1])
	print(h,"tag wali == ",st)
	#print(h)	
	#print(l)
	if len(h):				
			
				ma=0
				for i in range(len(h)):
					if fuzz.token_set_ratio(h[i],st) > fuzz.token_set_ratio(h[ma],st):
						ma=i
				p=h[ma]
	
				for i in range(len(h)):
					if fuzz.token_set_ratio(h[i],st) == fuzz.token_set_ratio(h[ma],st) and i != ma and fuzz.token_set_ratio(h[ma],st)!= 100 :
						print("see here")
						store_ratio=fuzz.token_set_ratio(h[ma],st)
						for x in l:
							if x[1] == p:
								store_last_added=x[0]				
						return 2	
				
				for x in l:
					if x[1] == p:
						print("123store ratio", store_ratio)	
						print("current ratio",fuzz.token_set_ratio(h[ma],st))
						
						
						if fuzz.token_set_ratio(h[ma],st) == 100:
							bus_st.add(x[0])				#check this
							store_ratio=29
							store_last_added=''							
							
							print("added",x[0])
							return 1
						
						elif store_ratio > fuzz.token_set_ratio(h[ma],st):
							
							bus_st.add(store_last_added)				#check this
							store_ratio=29
							store_last_added=''							
							
							print("added",x[0])
							return 1
						elif fuzz.token_set_ratio(h[ma],st) >= store_ratio   :
							store_ratio=fuzz.token_set_ratio(h[ma],st)
							store_last_added=x[0]
							return 2	
						
	return 0	
					

#this is used when no tag and no more token left in copy_next
def match_in_list_no_tag(l,st):
	#print("in no tag:")
	global store_ratio
	global store_last_added	

	h=[]
	for x in l:
		#temp=x.lower().replace('.',' ')  changes made here..
		temp=' '.join(re.findall(r"[\w.\"']+", x.lower().replace('.',' ')))
		#print(temp)
		if fuzz.token_set_ratio(temp,st) >=70 and fuzz.partial_ratio(temp,st) >30 :
				h.append([x,temp])
				
	print(h,"st == ",st)
	#print(h)	
	if len(h):				
			
				ma=0
				for i in range(len(h)):
					if fuzz.token_set_ratio(h[i][1],st) > fuzz.token_set_ratio(h[ma][1],st):     #ratio needed for muncipal school
						ma=i							   #partial ratio for acharya garden
				p=h[ma][1]										#token set for sradar nagar 4
				print("max is ",p)
				print("cr,sr",fuzz.token_set_ratio(h[ma][1],st),store_ratio)
				for i in range(len(h)):
					if fuzz.token_set_ratio(h[i],st) == fuzz.token_set_ratio(h[ma],st) and i != ma:				
						if fuzz.ratio(h[i],st)>fuzz.ratio(h[ma],st):
							ma=i	
				
				#for x in l:
				#	if x[1] == p:
				#		print("store ratio", store_ratio)	
				#		print("current ratio",fuzz.ratio(h[ma],st))
				#		if store_ratio > fuzz.ratio(h[ma],st) or  store_ratio ==29:						
				#			store_ratio=fuzz.ratio(h[ma],st)
				#			store_last_added=x[0]
				#			bus_st.add(x[0])
				#			print("added",x[0])
				#			store_ratio=29
				#			return 1
				if store_ratio > fuzz.token_set_ratio(h[ma][1],st) :
					if store_ratio == 29:
						return 0				
					print("adding",store_last_added)				
					bus_st.add(store_last_added)
					store_ratio=29
					store_last_added=''					
					
					token=re.findall(r"[\w.\"']+", st)
					for n in token[:-1]:
						copy_next.remove(n)
					print(copy_next)
					return 1

				else:
					bus_st.add(h[ma][0])
					token=re.findall(r"[\w.\"']+", st)
					for n in token:
						copy_next.remove(n)
					return 1	
	return 0	


#used when no tag
def match(l,st):
	global store_ratio
	global store_last_added	

	h=[]
	for x in l:
		temp=x.lower().replace('.',' ')
		if fuzz.token_set_ratio(temp,st) >=63	 and  fuzz.ratio(temp,st)>29:
				h.append([x,temp])
				
	print(h,"hst == ",st)
	#print(h)	
	if len(h):				
			
				ma=0
				for i in range(len(h)):
					if fuzz.ratio(h[i][1],st) > fuzz.ratio(h[ma][1],st):
						ma=i
				p=h[ma][1]
				
				print("max is ",p)
				print("sr,cr",store_ratio,fuzz.ratio(h[ma][1],st))				
	
				for i in range(len(h)):
					if fuzz.ratio(h[i][1],st) == fuzz.ratio(h[ma][1],st) and i != ma:
						store_ratio=fuzz.ratio(h[ma][1],st)
						store_last_added=h[ma][0]				
						return 2	
					
				if store_ratio > fuzz.ratio(h[ma][1],st):
					bus_st.add(store_last_added)
					print(store_ratio,fuzz.ratio(h[ma][1],st)	)
					print("added1",store_last_added)
					
					store_ratio=29
					store_last_added=''
					return 1
				elif fuzz.ratio(h[ma][1],st) >= store_ratio:
					print("current ratio *****",fuzz.ratio(h[ma][1],st))
					print("store_ratio*****",store_ratio)
					store_ratio=fuzz.ratio(h[ma][1],st)
					store_last_added=h[ma][0]
					return 2
	elif store_last_added != '':
		bus_st.add(store_last_added)
		print("added",store_last_added)
					
		store_ratio=29
		store_last_added=''
		return 1
				
			
	return 0

				
			

#used to find continuous tags and the corresponding station
def first(tag_list,start,end):
	global store_ratio
	global store_last_added

	com_tag=''
	temp = start+1
	while temp < end:
		com_tag=com_tag + ' ' + str(tag_list[temp][0])
		temp+=1
	com_tag=com_tag.strip()
	
	#print(com_tag)
	
	l=copy[:start]
	l.reverse()
	print("the list ",l)
	check_list=eval(tag_list[start][0])	
		
	para='' +com_tag
	h=0	
	for h in range(len(l)):		
			para=str(l[h])+' '+para
			i=match_in_list(check_list,para)
			if i == 2 and store_last_added !='':
				if h==len(l)-1:
					bus_st.add(store_last_added)
					r=0
				
					while r != h+1 :
						copy.remove(l[r])
						copy_next.remove(l[r])
						r+=1
					r=start
					while r!=end:
						print(r)
						print(copy)
						print(copy_next)
						print("new tag list",tag_list)
						copy.remove(tokenize[r])
						copy_next.remove(tokenize[r])
						r+=1
					print("!!!",copy)
					print("@@@",copy_next)
				continue
			if i == 1:
				r=0
				print("h is: "+str(h))
				print("check",copy,copy_next)
				while r != h+1 :
					print("removing",l[r])
					copy.remove(l[r])
					copy_next.remove(l[r])
					r+=1
				print("here",copy)
				print("there",copy_next)
				r=start
				while r!=end:
					#print("#new tag list",tag_list)
					copy.remove(tokenize[r])
					copy_next.remove(tokenize[r])
					r+=1
				print("##",copy)
				print("##",copy_next)
					
				print("#copy_next becomes",copy_next)
				return
			
			if i==0 and store_last_added!='':
				bus_st.add(store_last_added)
				store_last_added=''
				store_ratio=29
				
				r=0
				print("h is: "+str(h))
				print("check",copy,copy_next)
				while r != h+1 :
					print("removing",l[r])
					copy.remove(l[r])
					copy_next.remove(l[r])
					r+=1
				r=start
				while r!=end:
					#print("#new tag list",tag_list)
					copy.remove(tokenize[r])
					copy_next.remove(tokenize[r])
					r+=1
				print("##",copy)
				print("##",copy_next)
					
				#print("#copy_next becomes",copy_next)
				return

def match_bus(h,st):
	global store_bus	
	l=[]
	for x in h:
		temp=x
		no_list=re.findall(r'\d+',x)
		for n in no_list:
			temp=x.replace(n,' ' + n + ' ')
		temp=temp.lower().replace('-',' ').replace('.',' ')
		temp=' '.join(temp.split())
		if fuzz.token_set_ratio(st,temp)>60:
				l.append([x,temp])
	print("buses",l)
	ma=0
	
	if len(l):
		for i in range(len(l)):
			if partial_ratio2(st,l[i][1]) > partial_ratio2(st,l[ma][1]):
				ma=i
		p=l[ma][1]
		
		for i in range(len(l)):
			if partial_ratio2(st,l[i][1]) == partial_ratio2(st,l[ma][1]) and i!=ma:
				print(l[i][1],l[ma][1])
				store_bus=l[ma][1]
				return 2
		
		print("found bus",l[ma][0])
		bus_no_l.add(l[ma][0])
		return 1
	return 0

def find_bus(tokenize):
	global store_bus	

	st=' '.join(tokenize)
	no_list=re.findall(r'\d+',' '.join(tokenize))
	
	if not len(no_list):
		match_bus(bus_no,st)	
		
	for h in no_list:
		st=st.replace(h,' ' + h + ' ')
	token=st.split()	
	
		
	for  x in no_list:
		i=token.index(x)
		print(no_list,i,token)
		s=''
		for z in range(3):
			if i-1>=0 and i-1<len(token):
				s=s + ' ' + token[i-1]
			else:
				i+=1
				continue	
			print(s)
			i+=1
		s=s.strip()
		print("st==" ,s)
		m=match_bus(bus_no,s)
		if m==2:
			try:
				s=s+ ' ' +token[i-1]
				match_bus(bus_no,s)
			except Exception:
				bus_no_l.add(store_bus)
				print("found bus",store_bus)
				store_bus=''


			






def final(so):
	global store_ratio				#default value of stored ratio
	global store_last_added				
	global store_bus
	global bus_stops,station,bus,east,west,nagar,park,marg,depot,udaan,chowk,village,terminus,extension,colony,pada,garden,bus_no 
	
	s=so.lower()
	s=s.replace('.',' ')						#text to process
	global tokenize

	global bus_st,bus_no_l,copy_next,copy
	bus_st=set()
	bus_no_l=set()						#set to store the bus stops
	
	f1=open(join(settings.DATA_DIR, "bus_no.txt"))			
	bus_no=f1.readlines()

	#removing \n
	for i in range(len(bus_no)):
			t=""
			for ch in bus_no[i]:
				if ch!='\n':
					t=t+ch
			bus_no[i]=t
	f1.close()
	
	
	tokenize=re.findall(r"[\w.\"']+", s)			
	print("tokenize",tokenize)

	find_bus(tokenize)

	if len(bus_no_l):
		return "found bus " + str(list(bus_no_l)[0])


	tags=nltk.pos_tag(tokenize)
	
	remov=['IN','PRP','TO','CC']

	toks=[]
	for t in tags:
		if t[1] not in remov:
			toks.append(t[0])

	s=' '.join(toks)

	remov_next=['IN','PRP','CC']
	toks_next=[]
	for t in tags:
		if t[1] not in remov_next:
			toks_next.append(t[0])

	s=' '.join(toks_next)
	
	t=toks_next
	copy_next=t[:]
	copy_2=copy_next[:]
	tokenize = toks						
	print("tokenize",tokenize)

	copy=tokenize[:]					#original - conjunctions/prepositions etc
	tag_list=[]						#to store all the tags

	for x in copy:
		tag_list.append(get_tag_list(x))

	print(tag_list)





	change=0						
	length=0
	start=-1
	x=0
	while True:
		if x<len(tag_list): 
			length=len(tag_list[x])
			if length == 1 and change == 0:
				start = x
				change=1
				if x == len(tag_list)-1:
					first(tag_list,start,x+1)
				
			elif length == 0 and change == 1  :
				first(tag_list,start,x)
				tag_list=tag_list[x:]
				tokenize=tokenize[x:]
				print("is this printd",tag_list)
				x=-1
				change=0
				length=0
				start=0	
			
			elif length ==0 and change == 0 and x ==len(tag_list)-1:
				x+=1
				continue
			elif length ==1 and change ==1 and x==len(tag_list)-1:
				first(tag_list,start,x+1)
		
			else:
				change=length

			x+=1
			continue
		else:
			break	

	print("copy_next",copy_next)

	#processing of the tokens left after removing the tags
	while len(copy_next)!=0:
		if len(copy_next)==1:
			if not match_in_list_no_tag(bus_stops,copy_next[0]):
				break
		else :
			j=1
			s=copy_next[0]
			while j < len(copy_next):
				s=s+' '+ copy_next[j]
				if j == len(copy_next)-1:
						i=match_in_list_no_tag(bus_stops,s)
						if i==0:
							if store_last_added!='':
								bus_st.add(store_last_added)
								store_last_added=''
								store_ratio=29
							#copy_next.pop(0)			#changes done here
							#copy_next.pop(0)
							token=re.findall(r"[\w.\"']+", s)
							for n in token[:-1]:
								copy_next.remove(n)
						if not len(copy_next):
							break
						else: 
							continue
				i=match(bus_stops,s)
				if i==2:
						j+=1
						continue
					
				elif i==0:
					#copy_next.pop(0)			#changes made here
					#copy_next.pop(0)
					j+=1
					#break
					continue
				elif i==1:
					k=0
					while k<=j-1:
						copy_next.pop(0)
						k+=1
					print("copy_now_becomes",copy_next)
					break					
							
			
						


		
	
	print(bus_st)				#bus_st contains the stations in the query

	print(copy_next)

	
	if len(bus_st) == 2:
		return query1(so,list(bus_st))
	elif len(bus_st)==1:
		return query2(so,list(bus_st))	
	else:
		return 'invalid'

#h=raw_input("enter : ")
#print(final(h))
#andheri to ghatkopar