
#define rep(i,v) for(int i=0; i<(int) v.size(); i++)
typedef vector<double> row;
typedef vector<row> matrix;

//returns matrix of 0s
matrix zero(int n, int m) 
{
	return matrix(n, row(m, 0));
}

//returns the identity matrix all 0 except diagonals 1
matrix identity(int n)
{
	matrix ret = zero(n, n);
	rep(i,ret){
		ret[i][i] = 1;
	}
	return ret;
}

//returns the summation of diagonal (square matrix)
int matrixTrace(matrix &a) {
	int ret = 0;
	rep(i,a){
		ret += a[i][i];
	}
	return ret;
}

matrix rotate(matrix &a) {
	matrix ret = zero(a[0].size(), a.size()); //cols,rows
	rep(i,a){
		rep(j,a[i]){
			ret[j][a.size() - i - 1] = a[i][j]; //for CW rotation
			ret[j][i] = a[i][j]; // for transpose
		}
	}
	return ret;
}

matrix reflect(matrix &a) {
	matrix ret = zero(a.size(), a[0].size());
	rep(i,a){
		rep(j,a[i]){
			ret[i][a[0].size() - j - 1] = a[i][j];
		}
	}
	return ret;
}

//must be of equal size
matrix add(matrix &a, matrix &b) {
	matrix ret = zero(a.size(), a[0].size());
	rep(i,a){
		rep(j,a[i]){
			ret[i][j] = a[i][j] + b[i][j];
		}
	}
	return ret;
}

//add identity to a matrix
matrix addIdentity(const matrix &a) {
	matrix ret = a;
	rep(i,a){
		ret[i][i]++;
	}
	return ret;
}

matrix mult(const matrix &a, const matrix &b) {
	matrix ret = zero(a.size(), b[0].size());
	rep(i,a){
		rep(k,a[i]){
			if (a[i][k] == 0)
				continue; //skip
			rep(j,b[k]){
				ret[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return ret;
}

matrix pow(const matrix &a, ll k) {
	if (k == 0) {
		return identity(a.size());
	}

	if (k % 2 == 1) {
		return mult(a, pow(a, k - 1));
	}

	return pow(mult(a, a), k / 2);
}

//returns the summation of all matrices with powers from 0 to k
matrix sumpow(matrix &a, ll k){
	if(k == 0){
		return zero(a.size(),a.size());
	}

	if(k%2 == 1){
		return mult(a,addIdentity(sumpow(a,k-1)));
	}

	return mult(sumpow(a,k/2),addIdentity(pow(a,k/2)));
}

int fibMatrix(int n){
	if(n <= 1){
		return n;
	}
	//construct matrix
	// 0 1
	// 1 1
	matrix transition = zero(2,2);
	transition[0][1] = transition[1][0] = transition[1][1] = 1;

	// usually shifting is n - (dimension - 1)
	matrix transition_n = pow(transition, n - 1);
	matrix initial = zero(2,2);
	initial[0][1] = 1;

	matrix ret = mult(initial,transition_n);
	return ret[0][1];
}
