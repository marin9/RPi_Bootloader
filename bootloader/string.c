
void *memset(void *s, int c, int n){
	int p;
	char *m=(char*)s;

	for(p=0;p<n;p++){
		*m++=(char)c;
	}
	return s;
}

char *strcpy(char *dest, const char *src){
	int i=0;
	while(src[i]){
		dest[i]=src[i];
		++i;
	}
	dest[i]=0;
	return dest;
}

int atoi(char *str){
	int i=0, res=0;
    
    while(str[i]){
        res=res*10+str[i]-'0';
		++i;
    }
    return res; 
}

void itoa(char *str, int n){
	int i=0;
	int w=0;
	int d=1000000000;

	if(n<0){
		n=-n;
		str[i]='-';
		++i;
	}

	while(d){
		str[i]=n/d+'0';
		if(str[i]!='0'){
			w=1;
		}
		if(w){
			++i;
		}
		n=n%d;
		d/=10;
	}
	if(i==0){
		str[0]='0';
		str[1]=0;
	}else{
		str[i]=0;
	}
}
