
from datetime import datetime,timedelta
import sys
import os

#import mymail
import logging
import argparse

def checkarg():
	global symbol, subsymbol

        parser = argparse.ArgumentParser()
        
	parser.add_argument('-symbol',action='store', help = " eg GCJ8 " )
        parser.add_argument('-subsymbol',action='store', help = " eg GC " )

        args = parser.parse_args()
        symbol=args.symbol
        subsymbol=args.subsymbol
	
	
checkarg()

#folder ='/mnt_data/arvin/intraday/'
folder = "data/"
newsymbol=str(subsymbol)+'Python'
#log_file_path=folder+'merge.log'
#logging.basicConfig(filename=log_file_path,level=logging.DEBUG,format='%(asctime)s,%(levelname)s,%(message)s',)

sdt=(datetime.today()).strftime('%Y%m%d')
d = datetime.strptime(sdt,'%Y%m%d')
cds=d.strftime('%Y%m%d')
#print "cds = ",cds
#cds='20210325'
print "cds = ",cds," d = ",d ," std = ",sdt;
pdt=(datetime.today()-timedelta(days=1)).strftime('%Y%m%d')
pd = datetime.strptime(pdt,'%Y%m%d')
pds=pd.strftime('%Y%m%d')
#print "pds = ",pds
#pds='20210324'
print "pds = ",pds

fn=folder+str(cds)+'/'+str(subsymbol)+'Pricelog.txt'
#tfn = folder+str(subsymbol)+'TradePricelog.txt'
#tfn2=tfn

print "fn",fn
#print "tfn",tfn

'''
def getnext(fn):
	l = fn.readline()
	while l :
		lr=l.split(',')
		if len(lr) > 5 and lr[6]==symbol:
			lrt=lr[2]+lr[3]
			return lr,lrt
		l = fn.readline()
	return None,None

def getnext_bidask(fn):
        la = fn.readline()
        lb=fn.readline()
        while la and lb :
                lr=la.split(',')
                lrb=lb.split(',')
                if len(lr) > 5 and lr[6]==symbol and len(lrb)>5 and lrb[6]==symbol:
                        lrt=lr[2]+lr[3]
                        return lr,lrt,lrb
                la = fn.readline()
                lb =fn.readline()
        return None,None,None

def getlrt():
	return lastprint
	if lrt is None:
		return t_lrt[8:]
	elif t_lrt is None:
		return lrt[8:]
	else:
		return min(lrt[8:],t_lrt[8:])
'''

def gettlrt():
        return lastprint
        if t_lrt is None:
                return lrt[8:]
        elif lrt is None:
                return t_lrt[8:]
        else:
                return min(lrt[8:],t_lrt[8:])	
'''
def writeline():
        global prevseq,prevstr
        if ttq>0:
                if prevseq!=seq:
                        if prevseq!=0:
                                of.write(prevstr)
                        prevseq=seq
			prevstr=','.join((gettlrt(),newsymbol,bidq,str(bid),askq,str(ask),str(ltp),str(ttq)))+'\n'
'''
def writeline():
        global prevseq,prevstr
        if ttq>0:
                #if prevseq!=seq:
		if prevseq!=0:
			of.write(prevstr)
		prevseq=seq
		prevstr=','.join((gettlrt(),newsymbol,bidq,str(bid),askq,str(ask),str(ltp),str(ttq)))+'\n'

if not os.path.isfile(fn) :
        raise ValueError('Input file not found for merge')
else:
	if not os.path.isdir(folder +str(cds)):
		os.system("mkdir "+folder +str(cds))
	ofn = folder+str(cds)+"/"+newsymbol+'.csv'
	f = open(fn)
	#tf = open(tfn)
        of = open(ofn,'w')
        bid =0.0
        ask = 0.0
        bidq='0'
        askq='0'
        ltp=0.0
        ttq=0
        lrt=''
        t_lrt=''
        pbid=0
        pask = 0
        lastprint=''
        seq=0
        prevseq=0
        prevstr=''



	'''
	trade_file=open(tfn2,"r")
	ts=trade_file.readline()
	'''
	trade_seq=[]
	processed_seq=[]
	'''
	ts_larr=ts.split(',')
	while ts :
        	if len(ts_larr)>4:
                	trade_seq.append(ts_larr[4])
	        ts=trade_file.readline()
	        ts_larr=ts.split(',')
	trade_file.close()
	'''
	
	#larr,lrt=getnext(f)
	#t_larr,t_lrt=getnext(tf)
	#larr,lrt,barr=getnext_bidask(f)
	l=f.readline()
	larr=l.split(',')

	pds= "20210328"
	count =1
	if larr[0]==pds : #pds:
		while l:
			lr=l.split(',')
			if len(lr)>5 and lr[6]==symbol:
				if lr[9]!='A' and lr[9]!='B':
					ttq+=int(lr[10])
					seq=lr[4]
					ltp= float(lr[9])*float(lr[13])
					t_lrt=lr[2]+lr[3]
					trade_seq.append(lr[4])
					if bid<ask:
						#count+=1
						lastprint=t_lrt[8:]
						if seq not in processed_seq:
							processed_seq.append(seq)
                                       		writeline()
						pbid=bid
						pask = ask
				if lr[9]=='A' or lr[9]=='B':
					seq=lr[4]
					lrt=lr[2]+lr[3]
					lpair=f.readline()
					lrpair=lpair.split(',')
					if len(lrpair)>5 and lrpair[6]==symbol and lrpair[2]+lrpair[3]==lrt:
						count+=1
						#print(count, "-----> ",pbid ,bid ,pask, ask)
						if lr[9]=='A' and lrpair[9]=='B':
							bid=int(lrpair[10])*float(lrpair[12])
							bidq=lrpair[11]
							ask = int(lr[10])*float(lr[12])
							askq=lr[11]
						elif lr[9]=='B' and lrpair[9]=='A':
							ask=int(lrpair[10])*float(lrpair[12])
							askq=lrpair[11]
							bid = int(lr[10])*float(lr[12])
							bidq=lr[11]
						if (pbid!=bid or pask !=ask) and bid<ask :
							#count+=1
							lastprint =lrt[8:]
							#if seq not in trade_seq:
							if seq not in processed_seq:
								processed_seq.append(seq)
							writeline()
							pbid = bid
							pask = ask
			

        		l=f.readline()
	of.write(prevstr)
#print(count)

