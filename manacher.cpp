#include<bits/stdc++.h>

/*
 * Manacher's algorithm - finds palindromes' rs on each position i.
 * The total number of palindromes is equal to sum of R[i] and R[i+1], 0 <= i < n
 * O(n)
 */

using namespace std;

int main()
{
	ios_base::sync_with_stdio(0);
	string s;
	cin >> s;
	s = '1' + s + '2';
	int n = s.size();
	int *R = new int[n], *R1 = new int[n];
	int j=0;
	for(int i=0; i < n-1;) //Palindromes of even lengths
	{
		while(s[i-j] == s[i+1+j])
			j++;
		R[i] = j;
		int k=1;
		while(k <= R[i] && R[i]-k!=R[i-k])
		{
			R[i+k] = min(R[i-k], R[i]-k);
			k++;
		}
		j = max(0, j-k);
		i+=k;
	}
	
	j=0;
	R1[0] = 1;
	for(int i=1; i < n-1;) //Palindromes of odd lengths
	{
		while(s[i-j] == s[i+j])
			j++;
		R1[i] = j;
		int k=1;
		while(k < R1[i] && R1[i]-k!=R1[i-k])
		{
			R1[i+k] = min(R1[i-k], R1[i]-k);
			k++;
		}
		j = max(0, j-k);
		i+=k;
	}
	
	
	return 0;
}
