long long int mod = 1e9+7;//check
template<typename T>
class mat{
public:
	int r, c;//be sure to call te constructor to set r and c(must!!!!?? very important)
	vector<vector<T> > m;
	mat(int rr=0, int cc=0){
		m.resize(rr);
		for(auto &v: m){
			v.resize(cc);
		}
		r = rr;
		c = cc;
	}
	void makeidentity(){
		for(int i=0; i<r; i++){
			for(int j=0; j<c; j++){
				if(i==j) m[i][j] = 1;
				else m[i][j] = 0;
			}
		}
	}
	mat operator + (const mat &o) const {
		int row = o.r;
		int col = o.c;
		mat res(row, col);
		for(int i=0; i<row; i++){
			for(int j=0; j<col; j++){
				res.m[i][j] = (m[i][j] + o.m[i][j])%mod;
			}
		}
		return res;
	}
	
	mat operator - (const mat &o) const {
		int row = o.r;
		int col = o.c;
		mat res(row, col);
		for(int i=0; i<row; i++){
			for(int j=0; j<col; j++){
				res.m[i][j] = (m[i][j] - o.m[i][j])%mod;
				res.m[i][j] = (res.m[i][j]+mod+mod)%mod;
			}
		}
		return res;
	}
	
	mat operator * (const mat &o) const {
		//int row = o.r;
		int col = o.c;
		mat res(r, col);
		for(int i=0; i<r; i++){
			for(int j=0; j<col; j++){
				T all = 0;
				for(int k=0; k<c; k++){
					all = (all+m[i][k]*o.m[k][j])%mod;
				}
				res.m[i][j] = all;
			}
		}
		return res;
	}
	mat operator ^ (long long int b) const {
		mat<T> res(r, c);
		res.makeidentity();
		mat<T> gg = *this;
		while(b){
			if(b%2){
				res = (res*gg);
			}
			gg = gg*gg;
			b/=2;
		}
		return res;
	}
};
