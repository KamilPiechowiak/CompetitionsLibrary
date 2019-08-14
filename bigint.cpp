#include<bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vll;
#define PB push_back

int base = 1e2;
int bs = 2;
/*
 * 1e9 if only addition and subtraction,
 * 1e6 if also multiplication and division,
 * if using fft base*base*n <= 1e10
 */

struct BigInt {
		vi v;
	public:
		template<class T>
		void fromNumber(T a)
		{
			v.clear();
			if(a==0)
				v.PB(0);
			while(a)
			{
				v.PB(a%base);
				a/=base;
			}
		}
		
		void fromString(string a)
		{
			v.clear();
			int len = 0, b=base;
			while(b>1)
			{
				len++;
				b/=10;
			}
			for(int i=a.size()-1; i >= 0; i-=len)
			{
				int x=0, p=1;
				for(int j=0; j < len && i-j >=0; j++)
				{
					x+=int(a[i-j]-48)*p;
					p*=10;
				}
				v.PB(x);
			}
		}
		
		void norm()
		{
			for(int i=v.size()-1; i>0; i--)
			{
				if(v[i]==0)
					v.erase(v.end()-1);
				else
					break;
			}
		}
};
typedef BigInt bi;

string allDigits(int a)
{
	string res="";
	while(a)
	{
		res = char(a%10+48) + res;
		a/=10;
	}
	while(res.size() < bs)
		res = '0' + res;
	return res;
}

ostream& operator<<(ostream &stream, bi A)
{
	int i;
	for(i=A.v.size()-1; i >= 0 && A.v[i] == 0; i--);
	
	if(i < 0)
	{
		stream << 0;
		return stream;
	}
	stream << A.v[i];
	i--;
	for(; i >= 0; i--)
		stream << allDigits(A.v[i]);
	return stream;
}

bool operator<(const bi &A, const bi &B)
{
	if(A.v.size() > B.v.size())
		return false;	
	if(A.v.size() < B.v.size())
		return true;
	for(int i=A.v.size()-1; i>=0; i--)
	{
		if(A.v[i] > B.v[i])
			return false;
		if(A.v[i] < B.v[i])
			return true;
	}
	return false;
}

bool operator>(const bi &A, const bi &B)
{
	return B<A;
}

bool operator<=(const bi &A, const bi &B)
{
	return !(A>B);
}

bool operator>=(const bi &A, const bi &B)
{
	return !(A<B);
}

bool operator==(const bi &A, const bi &B)
{
	if(A>=B && A<=B)
		return true;
	return false;
}

bi operator+(const bi &A, const bi &B)
{
	bi C;
	int i;
	int car=0;
	for(i=0; i < min(A.v.size(), B.v.size()); i++)
	{
		int x = A.v[i] + B.v[i] + car;
		car = x/base;
		C.v.PB(x%base);
	}
	for(; i < A.v.size(); i++)
	{
		int x = A.v[i] + car;
		car = x/base;
		C.v.PB(x%base);
	}
	for(; i < B.v.size(); i++)
	{
		int x = B.v[i] + car;
		car = x/base;
		C.v.PB(x%base);
	}
	while(car)
	{
		C.v.PB(car%base);
		car/=base;
	}
	return C;
}

bi operator+(const bi &A, const int &b)
{
	bi B;
	B.fromNumber(b);
	return A+B;
}

bi operator-(const bi &A, const bi &B)
{
	bi C;
	int car=0, i;
	for(i=0 ; i < B.v.size(); i++)
	{
		int x = A.v[i]-B.v[i]+car;
		car = 0;
		if(x < 0)
		{
			car=-1;
			x+=base;
		}
		C.v.PB(x);
	}
	for(; i < A.v.size(); i++)
	{
		int x = A.v[i]+car;
		car=0;
		if(x<0)
		{
			car=-1;
			x+=base;
		}
		C.v.PB(x);
	}
	C.norm();
	return C;
}

bi operator-(const bi &A, const int &b)
{
	bi B;
	B.fromNumber(b);
	return A-B;
}

bi kar(const bi &A, const bi &B)
{
	int e = max(A.v.size()/2, B.v.size()/2);
	if(e<=128)
	{
		vll a(A.v.begin(), A.v.end());
		vll b(B.v.begin(), B.v.end());
		vll c(A.v.size() + B.v.size(), 0);
		for(int i=0; i < a.size(); i++)
		{
			for(int j=0; j < b.size(); j++)
			{
				c[i+j] += (ll)a[i]*b[j];
			}
		}
		ll car=0;
		for(int i=0; i < c.size(); i++)
		{
			c[i]+=car;
			car = c[i]/base;
			c[i] = c[i]%base;
		}
		vi Cn(c.begin(), c.end());
		bi C;
		C.v = Cn;
		C.norm();
		return C;
	}
	bi a, b, c, d;
	int i;
	for(i=0; i < min(e, (int)A.v.size()); i++)
		b.v.PB(A.v[i]);
	if(i>=A.v.size())
		a.fromNumber(0);
	else
		for(; i < A.v.size(); i++)
			a.v.PB(A.v[i]);
	for(i=0; i < min(e, (int)B.v.size()); i++)
		d.v.PB(B.v[i]);
	if(i>=B.v.size())
		c.fromNumber(0);
	else
		for(; i < B.v.size(); i++)
			c.v.PB(B.v[i]);
	bi p, q, r;
	p = kar(a, c);
	q = kar(a+b, c+d);
	r = kar(b, d);
	q = q-p-r;
	vll Cn(A.v.size()+B.v.size(), 0);
	for(i=0; i < r.v.size(); i++)
		Cn[i]+=r.v[i];
	for(i=0; i < q.v.size(); i++)
		Cn[i+e]+=q.v[i];
	for(i=0; i < p.v.size(); i++)
		Cn[i+2*e]+=p.v[i];
	for(int i=0; i < Cn.size()-1; i++)
	{
		Cn[i+1]+=Cn[i]/base;
		Cn[i]%=base;
	}
	vi Cn2(Cn.begin(), Cn.end());
	bi C;
	C.v = Cn2;
	C.norm();
	return C;
}

typedef complex<double> cd;
typedef vector<cd> vcd;


vcd fft(int n, cd omega, const vcd &A)
{
	if(n==1)
	{
		return A;
	}
	int n2=n>>1;
	vcd x, y;
	for(int i=0; i < n; i++)
	{
		if(i%2)
			y.PB(A[i]);
		else
			x.PB(A[i]);
	}
	x=fft(n2, omega*omega, x);
	y=fft(n2, omega*omega, y);
	vcd C(n, 0);
	cd m=1;
	for(int i=0; i < n2; i++)
	{
		C[i]= x[i] + m*y[i];
		C[i+n2] = x[i] - m*y[i];
		m = m*omega;
	}
	return C;
}

bi mltply(const bi &A, const bi &B)
{
	vcd a(A.v.begin(), A.v.end());
	vcd b(B.v.begin(), B.v.end());
	int d=a.size()+b.size()-1;
	int n=1;
	while(d)
	{
		d=d>>1;
		n=n<<1;
	}
	while(a.size() < n)
		a.PB(0);
	while(b.size() < n)
		b.PB(0);
	cd omega = polar((double)1, 2*M_PI/(double)n);
	a=fft(n, omega, a);
	b=fft(n, omega, b);
	for(int i=0; i < n; i++)
	{
		a[i]=a[i]*b[i];
	}
	a=fft(n, (cd)1/omega, a);
	vll Cn;
	for(int i=0; i < n; i++)
	{	
		Cn.PB(round(a[i].real()/n));
	}
	for(int i=0; i < n-1; i++)
	{
		Cn[i+1]+=Cn[i]/base;
		Cn[i]%=base;
	}
	vi Cn2(Cn.begin(), Cn.end());
	bi C;
	C.v = Cn2;
	C.norm();
	return C;
}

bi operator*(const bi &A, const bi &B)
{	
	//return mltply(A, B);
	return kar(A,B);
}

bi operator/(const bi &A, const int &b)
{
	vll a(A.v.begin(), A.v.end());
	for(int i=a.size()-1; i>=0; i--)
	{
		if(i>0)
			a[i-1]+=(a[i]%b)*base;
		a[i]/=b;
	}
	vi Cn(a.begin(), a.end());
	bi C;
	C.v = Cn;
	C.norm();
	return C;
}

vi mlt(vll &a, ll x)
{
	vll c;
	ll car=0;
	for(int i=0; i < a.size(); i++)
	{
		c.PB((ll)a[i]*x+car);
		car = c[i]/base;
		c[i]%=base;
	}
	while(car)
	{
		c.PB(car);
		car/=base;
	}
	vi c2 (c.begin(), c.end());
	return c2;
}

bi operator/(const bi &A, const bi &B)
{
	if(B.v.size() == 1)
	{
		return A/B.v[0];
	}
	bi Ap = A;
	if(A.v.size() < B.v.size())
	{
		bi C;
		C.fromNumber(0);
		return C;
	}
	vll c (A.v.size() - B.v.size() + 1, 0);
	int j = B.v.size() - 1;
	int i = A.v.size() - 1;
	for(; i >= j; i--)
	{
		ll x = 0;
		if(i-1 < Ap.v.size())
			x+=(ll)Ap.v[i-1];
		if(i < Ap.v.size())
			x+=(ll)Ap.v[i]*base;
		if(i+1 < Ap.v.size())
			x+=(ll)Ap.v[i+1]*base*base;
		ll y = (ll)B.v[j]*base + B.v[j-1];
		c[i-j] = x/y;
		vll Bp (i-j, 0);
		for(int k=0; k < B.v.size(); k++)
		{
			Bp.PB((ll)B.v[k]);
		}
		bi b3;
		b3.v = mlt(Bp, c[i-j]);
		b3.norm();
		if(b3 > Ap)
			c[i-j]--;
		b3.v = mlt(Bp, c[i-j]);
		b3.norm();
		Ap = Ap-b3;
	}
	vi c2(c.begin(), c.end());
	bi C;
	C.v = c2;
	C.norm();
	return C;
}

bi operator%(const bi &A, const bi &B)
{
	return (A - (A/B)*B);
}

int main()
{
	ios_base::sync_with_stdio(0);
	int t;
	cin >> t;
	while(t--)
	{
		bi a, b;
		string x, y;
		cin >> x >> y;
		a.fromString(x);
		b.fromString(y);
		cout << a*b << endl;
	}
	
	return 0;
}
