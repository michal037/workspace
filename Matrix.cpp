/* Michal Kozakiewicz 21859; 16 stycznia 2019 r. */

#include <iostream>

using namespace std;

class Matrix {
private:
	unsigned int size;
	double **data;

public:
	Matrix(const unsigned int size) {
		this->size = size;

		/* allocate memory */
		this->data = new double *[this->size];
		for (unsigned int i = 0; i < this->size; i++) {
			this->data[i] = new double[this->size];

			/* set zeros */
			for (unsigned int k = 0; k < this->size; k++) {
				this->data[i][k] = 0;
			}
		}
	}

	Matrix(const Matrix& m) {
		this->size = m.size;

		/* allocate memory */
		this->data = new double *[this->size];
		for (unsigned int i = 0; i < this->size; i++) {
			this->data[i] = new double[this->size];

			/* copy */
			for (unsigned int k = 0; k < this->size; k++) {
				this->data[i][k] = m.data[i][k];
			}
		}
	}

	virtual ~Matrix() {
		for (unsigned int i = 0; i < this->size; i++) {
			delete []this->data[i];
		}

		delete []this->data;
	}

	friend ostream& operator<<(ostream& in, const Matrix& m);

	double* operator[](unsigned int i) {
		return this->data[i];
	}

	Matrix& operator=(const Matrix& m) {
		for (unsigned int i = 0; i < m.size; i++) {
			for (unsigned int k = 0; k < m.size; k++) {
				this->data[i][k] = m.data[i][k];
			}
		}

		return *this;
	}

	Matrix operator+(const Matrix& m) {
		Matrix out(*this);

		for (unsigned int i = 0; i < this->size; i++) {
			for (unsigned int k = 0; k < this->size; k++) {
				out.data[i][k] += m.data[i][k];
			}
		}

		return out;
	}

	Matrix operator*(const double val) {
		Matrix out(*this);

		for (unsigned int i = 0; i < this->size; i++) {
			for (unsigned int k = 0; k < this->size; k++) {
				out.data[i][k] *= val;
			}
		}

		return out;
	}

	friend Matrix operator*(const double val, const Matrix& m);
};

ostream& operator<<(ostream& in, const Matrix& m) {
	for (unsigned int i = 0; i < m.size; i++) {
		for (unsigned int k = 0; k < m.size; k++) {
			in << m.data[i][k] << " ";
		}

		in << endl;
	}

	return in;
}

Matrix operator*(const double val, const Matrix& m) {
	Matrix out(m);

	for (unsigned int i = 0; i < out.size; i++) {
		for (unsigned int k = 0; k < out.size; k++) {
			out.data[i][k] *= val;
		}
	}

	return out;
}

int main(int argc, char** argv)
{
	Matrix A(3);
	A[0][0] = 1;
	A[0][1] = 4;

	Matrix B(A);
	B[1][1] = 1;
	B[2][2] = 3;

	Matrix C(3);
	C = 1.5 * A + B * 3.5;

	cout << "Mat A:\n" << A << endl;
	cout << "Mat B:\n" << B << endl;
	cout << "Mat C:\n" << C << endl;

	return 0;
}
