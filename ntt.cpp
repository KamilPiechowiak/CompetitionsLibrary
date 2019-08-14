// mod = 1051721729 = 1003*2^20+1
// power omega inverse(power)
// 2^4 132687779 985989121
// 2^5 68640796 1018855425
// 2^6 273536497 1035288577
// 2^7 1039141327 1043505153
// 2^8 195323409 1047613441
// 2^9 1014031751 1049667585
// 2^10 550976676 1050694657
// 2^11 437488385 1051208193
// 2^12 299356529 1051464961
// 2^13 83974713 1051593345
// 2^14 985455169 1051657537
// 2^15 332131397 1051689633
// 2^16 789600351 1051705681
// 2^17 410021621 1051713705
// 2^18 460456117 1051717717
// 2^19 53521046 1051719723
// 2^20 531741956 1051720726


vector<ll> omega;
const int n = (1<<18);
const int p = 1051721729;

void initFFT() {
    omega.resize(n);
    omega[0] = 1;
    ll om = 460456117;
    for(int i=1; i < n; i++) {
        omega[i] = (omega[i-1]*om)%p;
    }
}

void fft(vector<ll> &v, vector<ll> &u, int le, int ri, int d) {
    int m = ri-le+1;
    if(m == 1) {
        return;
    }
    for(int i=0; i < m/2; i++) {
        u[le+i] = v[le+2*i];
        u[le+i+m/2] = v[le+2*i+1];
    }
    fft(u, v, le, le+m/2-1, 2*d);
    fft(u, v, le+m/2, ri, 2*d);
    int j=0;
    for(int i=0; i < m/2; i++) {
        v[le+i] = (u[le+i] + omega[j]*u[le+i+m/2])%p;
        v[le+i+m/2] = (u[le+i] + omega[j+n/2]*u[le+i+m/2])%p;
        j+=d;
    }
}

void fft(vector<ll> &v) {
    vector<ll> u;
    u.resize(v.size());
    fft(v, u, 0, v.size()-1, 1);
}

void ifft(vector<ll> &v) {
    fft(v);
    for(int i=1; i < v.size()/2; i++) {
        swap(v[i], v[v.size()-i]);
    }
    for(int i=0; i < v.size(); i++) {
        v[i]=((v[i]*1051717717)%p+p)%p;
    }
}
