// 9 Collect Third Terms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

const string delim = "\\";
const string out_res = "results";

void findCos(int **m, int  size, int n, int &da, int &db)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			if (m[i][j] == n)
			{
				da = j;
				db = i;
				break;
			}
		}
	da = da - size / 2;
	db = -db + size / 2;
}

struct st
{
	string name;
	//new
	int len;
	string Type;//C,S or J
	char ops[10];
	int nums[10];
	//end new
	double value[10];
	bool operator==(st r)
	{
		if (name.compare(r.name) == 0)
			return true;
		else
			return false;
	};
};

struct stCosSer
{
	static const int NN = 10;
	int ka, kb;
	double val[NN];
	bool operator ==(stCosSer r)
	{
		if ((ka == r.ka) && (kb == r.kb))
			return true;
		else
			return false;
	}

};
struct stCos
{
	
	char name[2];
	vector<stCosSer> series;
	bool operator==(stCos r)
	{
		if ((name[0] == r.name[0]) && (name[1] == r.name[1]))
			return true;
		else
			return false;
	};
	
	
};

//new structures
struct term
{
	int len;
	int order;
	char ops[10];
	int nums[10];
	double value;
	
	void decompose(string s, double val)
	{
		int temp = s.find_first_not_of("Jpmz");
		len = temp - 1;
		for (int i = 0; i < len; i++)
			ops[i] = s[i + 1];
		istringstream is;
		char tc;
		is.str(s.substr(temp));
		for (int i = 0; i <len; i++)
		{
			is >> nums[i];
			is >> tc;
		}
		value = val;

	}
	void setOrder(int Ord)
	{
		order = Ord;
	}
	bool operator==(term next)
	{
		if (len != next.len)
			return false;
		for (int i = 0; i < len; i++)
		{
			if (ops[i] != next.ops[i])
				return false;
			if (nums[i] != next.nums[i])
				return false;
		}
		return true;
	}
};

struct a_op
{
	int n;//general length
	vector<char> names; //plus or minus
	vector<int> node; //to calc shift
	double coeff;
	int order;
	bool operator==(a_op sec)
	{
		if (n != sec.n)
			return false;
		for (int i = 0; i < n;i++)
		{
			if (names[i] != sec.names[i])
				return false;
			if (node[i] != sec.node[i])
				return false;
		}
		return true;
	}


};

struct Cos
{
	double factor;
	vector<int> ka, kb;
	bool operator ==(Cos c2)
	{
		if (ka.size() != c2.ka.size()||kb.size()!=c2.kb.size)
			return false;
		for (int i = 0; i < ka.size(); i++)
		{
			if (ka[i] != c2.ka[i] || kb[i] != c2.kb[i])
				return false;
		}
		return true;
	}
};

struct correction
{
	vector<char> in;
	char out[2];
	vector<Cos> cs;
	bool operator ==(correction c2)
	{
		for (int i = 0; i < in.size(); i++)
		{
			if (in[i] != c2.in[i])
				return false;
		}
		if (out[0] != c2.out[0] || out[1] != c2.out[1])
			return false;
		return true;
	}
	void add(Cos new_cos)
	{
		vector<Cos>::iterator it;
		it = find(cs.begin(), cs.end(), new_cos);
		if (it != cs.end())
		{
			it->factor += new_cos.factor;
		}
		else
			cs.push_back(new_cos);
	}
	//TODO
	//finish it
	void print(ofstream & outF)
	{
		if (in.size() == 1)  //for triple terms
		{
			
		}
		if (in.size() == 2)  //for quatro terms
		{
			if (in[0] == 'p'&&in[1] == 'p')
				outF << "Subsript[Fp,k]";
			if (in[0] == 'm'&&in[1] == 'm')
				outF << "Subsript[Fm,k]";
			if (in[0] == 'p'&&in[1] == 'm')
				outF << "Subsript[G,k]";
			if (in[0] == 'm'&&in[1] == 'p')
				outF << "Subsript[G,k]";
			outF << "*";
			if (out[0] == 'p'&&out[1] == 'p')
				outF << "Subsript[Fp,q]";
			if (out[0] == 'm'&&out[1] == 'm')
				outF << "Subsript[Fm,q]";
			if (out[0] == 'p'&&out[1] == 'm')
				outF << "Subsript[G,q]";
			outF << "*(";
			for (int i = 0; i < cs.size(); i++)
			{
				outF << cs[i].factor << "*Cos[";
				if (in[1] != in[0]) 
					outF << "ka*"<<cs[i].ka[1]<<+"kb*"<<cs[i].kb[1];
				else 
					outF << "ka*" << -cs[i].ka[1] << +"kb*"<<-cs[i].kb[1];
				outF << "+";
				outF << "qa*" << cs[i].ka[2] << +"qb*" << cs[i].kb[2];
				outF << "+";
				if (out[1] != out[2])
					outF << "qa*" << cs[i].ka[3] << +"qb*" << cs[i].kb[3];
				else
					outF << "qa*" << -cs[i].ka[3] << +"qb*" << -cs[i].kb[3];
				outF << "]";
				if (i != cs.size() - 1)
				{
					outF << "+";
				}
			}
		}

	}
};

int mask4[6][4] = { { 1, 1, 0, 0 }, { 1, 0, 1, 0 }, { 1, 0, 0, 1 }, { 0, 1, 1, 0 }, { 0, 1, 0, 1 }, { 0, 0, 1, 1 } };
class converter
{
	
	vector<term> shorterTerms;
	vector<a_op> a_ops_l;
	vector<correction> cors;
	double factor;
	int a_amount;
	void set(double F,int A_amount)
	{
		factor = F;
		a_amount = A_amount;
	}
	void decomposeTerm(term in)
	{
		if (a_amount == 3)
			decomposeTerm3(in);
		if (a_amount == 4)
			decomposeTerm4(in);
	}
	void insertShortTerm(term cur)
	{
		vector<term>::iterator it;
		it = find(shorterTerms.begin(), shorterTerms.end(), cur);
		if (it != shorterTerms.end())
			it->value += cur.value;
		else
			shorterTerms.push_back(cur);
	}
	
	void decomposeTerm3(term in)
	{
		term cur;
		cur.len = -1;
		double coeff = 1;

		int pm;
		for (int i = 0; i < in.len; i++)
			if (in.ops[i] != 'z')
				pm++;
		if (pm == 1)
		{
			cur.len = 2;
			cur.order = in.order;
			cur.value = in.value*coeff;
			cur.ops[0] = in.ops[0];
			cur.nums[0] = in.ops[0];
			if (in.ops[0] == 'z')
			{
				for (int i = 1; i < in.len; i++) //ищем первый pm оператор
					if (in.ops[i] != 'z')
					{
						cur.nums[1] = in.nums[i];
						cur.ops[1] = in.ops[i];
						insertShortTerm(cur);
						break;
					}
			}
			else //выбираем все доступные z операторы
			{
				for (int i = 1; i < in.len; i++)
				{
					cur.ops[1] = in.ops[1];
					cur.nums[1] = in.ops[1];
					insertShortTerm(cur);
				}
			}
		}
		if (pm == 3)
		{
			for (int i = 0; i < in.len - 3; i++)
				coeff *= factor;
			cur.len = 3;
			cur.order = in.order;
			cur.value = in.value*coeff;
			int index = 0;
			for (int i = 0; i < in.len; i++)
			{
				if (in.ops[i] != 'z')
				{
					cur.ops[index] = in.ops[i];
					cur.nums[index] = in.nums[i];
					index++;
				}
			}
			insertShortTerm(cur);
		}
		
	}
	void decomposeTerm4(term in)
	{
		term cur;
		cur.len = -1;
		double coeff = 1;
		
		int pm;
		for (int i = 0; i < in.len; i++)
			if (in.ops[i] != 'z')
				pm++;
		if (pm == 0)
		{
			cur.value = coeff*in.value;
			cur.order = in.order;
			cur.len = 2;
			for (int i = 0; i < in.len-2; i++)
					coeff *= factor;
			for (int i = 1; i < in.len; i++)//заменяем все подряд sz, поочереди оставляем только i
			{
				
				cur.ops[0] = 'z';
				cur.ops[1] = 'z';
				cur.nums[0] = in.nums[0];
				cur.nums[1] = in.nums[i];
				
				//вставляем
				insertShortTerm(cur);
			}			
		}
		if (pm == 2)
		{
			for (int i = 0; i < in.len - 3; i++)
				coeff *= factor;
			cur.len = 3;
			cur.value = coeff*in.value;
			cur.order = in.order;
			cur.nums[0] = in.nums[0];
			cur.ops[0] = in.ops[0];
			if (cur.ops[0] == 'z')//оставляем только pm-члены из оставшихся
			{
				int index = 1;
				for (int i = 1; i < in.len; i++)
				{
					if (in.ops[i] != 'z')
					{
						cur.ops[index] = in.ops[i];
						cur.nums[index] = in.nums[i];
						index++;
					}
				}
				//вставляем
				insertShortTerm(cur);
			}
			else //по очереди выбираем все z-члены
			{
				int index = 0;
				for (int i = 1; i < in.len;i++) //ищем второй pm оператор
					if (in.ops[i] != 'z')
					{
						index = i;
						break;
					}
				for (int i = 1; i < in.len; i++)
				{
					if (index < i)
					{
						cur.ops[1] = in.ops[index];
						cur.ops[2] = in.ops[i];
						cur.nums[1] = in.nums[index];
						cur.nums[2] = in.nums[i];
					}
					if (index > i)
					{
						cur.ops[1] = in.ops[i];
						cur.ops[2] = in.ops[index];
						cur.nums[1] = in.nums[i];
						cur.nums[2] = in.nums[index];
					}
					//вставляем
					insertShortTerm(cur);
				}
			}

		}

		if (pm == 4)
		{
			for (int i = 0; i < in.len - 4; i++)
				coeff *= factor;
			cur.len = 4;
			cur.order = in.order;
			cur.value = in.value*coeff;
			int index = 0;
			for (int i = 0; i < in.len; i++)
			{
				if (in.ops[i] != 'z')
				{
					cur.ops[index] = in.ops[i];
					cur.nums[index] = in.nums[i];
					index++;
				}
			}	
			//вставляем
			insertShortTerm(cur);
		}
	}

	void convertToAop()
	{
		int pm;
		a_op cur;
		for (int i = 0; i < shorterTerms.size(); i++)
		{
			pm = 0;
			cur.names.clear();
			cur.node.clear();

			for (int j = 0; j < shorterTerms[i].len; i++)
			{
				if (shorterTerms[i].ops[j] == 'z')
				{
					cur.names.push_back('p');
					cur.names.push_back('m');
					cur.node.push_back(shorterTerms[i].nums[j]);
					cur.node.push_back(shorterTerms[i].nums[j]);
				}
				else//pm-case
				{
					cur.names.push_back(shorterTerms[i].ops[j]);
					cur.node.push_back(shorterTerms[i].nums[j]);
				}
			}

			//vector<a_op>::iterator it = find(a_ops_l.begin(), a_ops_l.end(), cur);
			//if (it != a_ops_l.end())
			cur.coeff = shorterTerms[i].value;
			cur.order = shorterTerms[i].order;
			a_ops_l.push_back(cur);
		}
	}

	void convertToCorrections()
	{
		correction cur;
		int index;
		if (a_amount == 4)
		{
			for (int i = 0; i < a_ops_l.size(); i++)
			{
				cur.cs.clear();
				cur.in.clear();
				for (int j = 0; j < 6; j++)
				{
					index = 0;
					for (int k = 0; k < 4; k++)
					{
						if (mask4[j][k] == 0)
						{
							cur.in.push_back(a_ops_l[i].names[j]);
						}
						else
						{
							cur.out[index++] = a_ops_l[i].names[j];
						}
					}
					//eval cos for cur term
					Cos cur_cos;
					cur_cos.factor = a_ops_l[i].coeff;
					for (int k = 1; k < a_ops_l.size(); k++)
					{

					}
					//end eval
					vector<correction>::iterator it = find(cors.begin(), cors.end(), cur);
					if (it != cors.end())
					{
						it->cs.push_back(cur_cos);
					}
					else
					{
						cur.cs.push_back(cur_cos);
						cors.push_back(cur); 
					}
				}
			}

		}
	}

	void clearShortTerms()
	{
		shorterTerms.clear();
	}
};

//end new class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//vector<>
//end new
vector<st> res;
vector<st> long_res; 
vector<stCos> cos_res;
st c_res;
st a0a0;



void decompose(st &cur)
{
	if (cur.name[0] == 'C')
	{
		cur.len = 0;
		cur.Type = "C";
	}
	if (cur.name[0] == 'S')
	{
		cur.len = 1;
		cur.ops[0] = cur.name[1];
		istringstream is;
		is.str(cur.name.substr(2));
		is >> cur.nums[0];
		cur.Type = "S";
	}
	if (cur.name[0] == 'J')
	{
		int temp = cur.name.find_first_not_of("Jpmz");
		cur.len = temp - 1;
		for (int i = 0; i < cur.len; i++)
			cur.ops[i] = cur.name[i + 1];
		istringstream is;
		char tc;
		is.str(cur.name.substr(temp));
		for (int i = 0; i < cur.len; i++)
		{
			is >> cur.nums[i];
			is >> tc;
		}
		cur.Type = "J";
	}
}
int** matrix;

void fillMatrix(int **matrix, int NNN)
{
	int dir = 0;
	int d = max(1 + ((NNN) / 2) * 2, 1 + (NNN - 2) * 2);
	int s = d / 2;
	int cx, cy, ct, cb, cl, cr;
	dir = 0;//0- направо, 1-вверх, 2- налево, 3- вниз
	ct = cb = cl = cr = cx = cy = s;
	for (int curn = 0; curn<d*d; curn++)
	{
		matrix[cy][cx] = curn;
		switch (dir)
		{
		case 0:
			if (cx == cr)
			{
				cr++;
				cl--;
				cx++;
				dir = 1;
			}
			else
			{
				cx++;
			}
			break;
		case 1:
			if (cy == ct)
			{
				ct--;
				cb++;
				cy--;
				dir = 2;
			}
			else
			{
				cy--;
			}
			break;
		case 2:
		{
			cx--;
			if (cx == cl)
			{
				dir = 3;
			}
		}
		break;
		case 3:
		{
			cy++;
			if (cy == cb)
			{
				dir = 0;
			}
		}
		break;
		}
	}
	//!------------Matrix output--------------------
	for (int i = 0; i<d; i++)
	{
		for (int j = 0; j<d; j++)
		{
			cout << setw(3) << matrix[i][j] << " ";
		}
		cout << "\n";
	}
	//!-----------Output end
	ofstream nodenums("nodenums.txt", ios::out);

	nodenums << "{";
	for (int i = 0; i<d; i++)
	{
		nodenums << "{";
		for (int j = 0; j<d; j++)
		{
			if (j == d - 1)
				nodenums << matrix[i][j] << "}";
			else
				nodenums << matrix[i][j] << ",";
		}
		if (i<d - 1)
			nodenums << ",";
	}
	nodenums << "}";
	nodenums.close();


}

void findCos(int **m, int  size, int n, int &da, int &db)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			if (m[i][j] == n)
			{
				da = j;
				db = i;
				break;
			}
		}
	da = da - size / 2;
	db = -db + size / 2;
}




int _tmain(int argc, _TCHAR* argv[])
{ 
	
	//init
	
	for (int i = 0; i < 10; i++)
	{
		c_res.value[i] = 0;
		a0a0.value[i] = 0;
	}
	//end init
	vector<string> points;
	ifstream config("config.txt", ios::in);
	int num_points,min_order,max_order,cur_term_len;
	string tmp;
	int PiPoint;
	getline(config, tmp);
	config >> num_points;
	getline(config, tmp);
	getline(config, tmp);
	config >> min_order >> max_order >> cur_term_len;
	getline(config, tmp);
	getline(config, tmp);
	config >> PiPoint;

	///init matrix
		int size = max(1 + ((max_order) / 2) * 2, 1 + (max_order - 2) * 2);
		int** m;
		m = new int*[size];
		for (int i = 0; i < size; i++)
			m[i] = new int[size];
		fillMatrix(m, max_order);
		int ka, kb;
		findCos(m, size, 21, ka, kb);
	
	//end init

	ifstream fpoints("points.txt", ios::in);
	string s,tmp_s;
	for (int i = 0; i < num_points;i++)
	{
		getline(fpoints, s);
		points.push_back(s);
	}
	fpoints.close();
	ostringstream fname;
	st temp;
	bool flag;
	ifstream valueFile;
	double temp_val;
	st temp_st,final_st;
	for (int i = 0; i < num_points; i++)
	{
		cout << i << "\n";
		double factor;
		if (stof(points[i]) - 0.551 > 0)
			factor = 0.5;
		else
			factor = -0.5;
		res.clear();
		for (int j = min_order; j <= max_order; j++)
		{
			cout << "Order " << j << "\n";
			fname.str("");
			fname << "d:\\Andrew\\Practice\\!!!_Last Set\\Temp1\\5 SumNum Term\\5 SumNum Term\\results\\" << points[i] << "\\" << j << "_results_" << points[i] << "_" << cur_term_len << ".txt";

			ifstream cur(fname.str(), ios::in);

			while (!cur.eof())
			{
				getline(cur, s);
				if (s.length() > 0)
				{
					istringstream iss;
					iss.str(s);
					iss >> temp_st.name >> temp_val;

					decompose(temp_st);
					flag = false;
					//if ((temp_st.len == 3) && (temp_st.ops[2] == 'z'))//заменяем 3-ий оператор
					//{
					//	final_st.len = 2;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.ops[1] = temp_st.ops[1];
					//	final_st.nums[0] = temp_st.nums[0];
					//	final_st.nums[1] = temp_st.nums[1];
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*factor;;
					//	final_st.name = "J";
					//	final_st.name = final_st.name + final_st.ops[0] + final_st.ops[1] + to_string(final_st.nums[0]) + "_" + to_string(final_st.nums[1]);
					//	int re = final_st.name.compare("Jzz0_8");
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor;
					//	else
					//		res.push_back(final_st);
					//}
					//if ((temp_st.len == 3) && (temp_st.ops[1] == 'z') && (temp_st.nums[2] < 9))//заменяем 2ой оператор
					//{
					//	final_st.len = 2;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.ops[1] = temp_st.ops[2];
					//	final_st.nums[0] = temp_st.nums[0];
					//	final_st.nums[1] = temp_st.nums[2];
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*factor;
					//	final_st.name = "J";
					//	final_st.name = final_st.name + final_st.ops[0] + final_st.ops[1] + to_string(final_st.nums[0]) + "_" + to_string(final_st.nums[1]);
					//	int re = final_st.name.compare("Jzz0_8");
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor;
					//	else
					//		res.push_back(final_st);
					//}
					//if ((temp_st.len == 3) && (temp_st.ops[1] == 'z') && (temp_st.ops[2] == 'z') && (temp_st.nums[1] > 8 || temp_st.nums[2]>8))//заменяем оба
					//{
					//	final_st.len = 1;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.nums[0] = temp_st.nums[0];
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*(factor*factor);
					//	final_st.name = "Sz0";
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor*factor;
					//	else
					//		res.push_back(final_st);
					//}

					//////// temp_st.len==4
					//if ((temp_st.len == 4) && (temp_st.ops[1] == 'z') && (temp_st.ops[2] == 'z') && (temp_st.nums[3] <= 8))//заменяем два средних
					//{
					//	final_st.len = 2;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.nums[0] = temp_st.nums[0];
					//	final_st.ops[1] = temp_st.ops[3];
					//	final_st.nums[1] = temp_st.nums[3];
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*(factor*factor);
					//	final_st.name = "J";
					//	final_st.name = final_st.name + final_st.ops[0] + final_st.ops[1] + to_string(final_st.nums[0]) + "_" + to_string(final_st.nums[1]);
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor*factor;
					//	else
					//		res.push_back(final_st);
					//}
					//if ((temp_st.len == 4) && (temp_st.ops[2] == 'z') && (temp_st.ops[3] == 'z') && (temp_st.nums[1] <= 8))//заменяем два средних
					//{
					//	final_st.len = 2;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.nums[0] = temp_st.nums[0];
					//	final_st.ops[1] = temp_st.ops[1];
					//	final_st.nums[1] = temp_st.nums[1];
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*(factor*factor);
					//	final_st.name = "J";
					//	final_st.name = final_st.name + final_st.ops[0] + final_st.ops[1] + to_string(final_st.nums[0]) + "_" + to_string(final_st.nums[1]);
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor*factor;
					//	else
					//		res.push_back(final_st);
					//}
					//if ((temp_st.len == 4) && (temp_st.ops[1] == 'z') && (temp_st.ops[3] == 'z') && (temp_st.nums[2] <= 8))//заменяем первый и последний
					//{
					//	final_st.len = 2;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.nums[0] = temp_st.nums[0];
					//	final_st.ops[1] = temp_st.ops[2];
					//	final_st.nums[1] = temp_st.nums[2];
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*(factor*factor);
					//	final_st.name = "J";
					//	final_st.name = final_st.name + final_st.ops[0] + final_st.ops[1] + to_string(final_st.nums[0]) + "_" + to_string(final_st.nums[1]);
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor*factor;
					//	else
					//		res.push_back(final_st);
					//}
					//if ((temp_st.len == 4) && (temp_st.ops[1] == 'z') && (temp_st.ops[2] == 'z') && (temp_st.ops[3] == 'z') && (temp_st.nums[1] > 8) && (temp_st.nums[2] >8) && (temp_st.nums[3] > 8))//заменяем два средних
					//{
					//	final_st.len = 1;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.nums[0] = temp_st.nums[0];
					//	
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*(factor*factor*factor);
					//	final_st.name = "Sz0";
					//	
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor*factor*factor;
					//	else
					//		res.push_back(final_st);
					//}

					////// 5 terms to quadratic 
					//if ((temp_st.len == 5) && (temp_st.ops[1] == 'z') && (temp_st.ops[2] == 'z') && (temp_st.ops[3] == 'z') && (temp_st.nums[4] <= 8))//заменяем первый и последний
					//{
					//	final_st.len = 2;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.nums[0] = temp_st.nums[0];
					//	final_st.ops[1] = temp_st.ops[4];
					//	final_st.nums[1] = temp_st.nums[4];
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*(factor*factor*factor);
					//	final_st.name = "J";
					//	final_st.name = final_st.name + final_st.ops[0] + final_st.ops[1] + to_string(final_st.nums[0]) + "_" + to_string(final_st.nums[1]);
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor*factor*factor;
					//	else
					//		res.push_back(final_st);
					//}
					//
					//if ((temp_st.len == 5) && (temp_st.ops[1] == 'z') && (temp_st.ops[2] == 'z') && (temp_st.ops[4] == 'z') && (temp_st.nums[3] <= 8))//заменяем первый и последний
					//{
					//	final_st.len = 2;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.nums[0] = temp_st.nums[0];
					//	final_st.ops[1] = temp_st.ops[3];
					//	final_st.nums[1] = temp_st.nums[3];
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*(factor*factor*factor);
					//	final_st.name = "J";
					//	final_st.name = final_st.name + final_st.ops[0] + final_st.ops[1] + to_string(final_st.nums[0]) + "_" + to_string(final_st.nums[1]);
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor*factor*factor;
					//	else
					//		res.push_back(final_st);
					//}

					//if ((temp_st.len == 5) && (temp_st.ops[1] == 'z') && (temp_st.ops[3] == 'z') && (temp_st.ops[4] == 'z') && (temp_st.nums[2] <= 8))//заменяем первый и последний
					//{
					//	final_st.len = 2;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.nums[0] = temp_st.nums[0];
					//	final_st.ops[1] = temp_st.ops[2];
					//	final_st.nums[1] = temp_st.nums[2];
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*(factor*factor*factor);
					//	final_st.name = "J";
					//	final_st.name = final_st.name + final_st.ops[0] + final_st.ops[1] + to_string(final_st.nums[0]) + "_" + to_string(final_st.nums[1]);
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor*factor*factor;
					//	else
					//		res.push_back(final_st);
					//}
					//if ((temp_st.len == 5) && (temp_st.ops[2] == 'z') && (temp_st.ops[3] == 'z') && (temp_st.ops[4] == 'z') && (temp_st.nums[1] <= 8))//заменяем первый и последний
					//{
					//	final_st.len = 2;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.nums[0] = temp_st.nums[0];
					//	final_st.ops[1] = temp_st.ops[1];
					//	final_st.nums[1] = temp_st.nums[1];
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*(factor*factor*factor);
					//	final_st.name = "J";
					//	final_st.name = final_st.name + final_st.ops[0] + final_st.ops[1] + to_string(final_st.nums[0]) + "_" + to_string(final_st.nums[1]);
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor*factor*factor;
					//	else
					//		res.push_back(final_st);
					//}
					//if ((temp_st.len == 5) && (temp_st.ops[1] == 'z') && (temp_st.ops[2] == 'z') && (temp_st.ops[3] == 'z') && (temp_st.ops[4] == 'z') && (temp_st.nums[1] > 8) && (temp_st.nums[2] > 8) && (temp_st.nums[3] > 8) && (temp_st.nums[4] > 8))//заменяем первый и последний
					//{
					//	final_st.len = 1;
					//	final_st.ops[0] = temp_st.ops[0];
					//	final_st.nums[0] = temp_st.nums[0];
					//	for (int l = 1; l <= max_order; l++)
					//		final_st.value[l] = 0;
					//	final_st.value[j] = temp_val*(factor*factor*factor);
					//	final_st.name = "S"+to_string(final_st.ops[0])+"0";
					//	//final_st.name = final_st.name + final_st.ops[0] + final_st.ops[1] + to_string(final_st.nums[0]) + "_" + to_string(final_st.nums[1]);
					//	flag = true;
					//	vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//	if (it != res.end())
					//		it->value[j] += temp_val*factor*factor*factor;
					//	else
					//		res.push_back(final_st);
					//}

					//////////////////////////////////////////////////////////////////////
					//convert to qudratic term
					//////////////////////////////////////////////////////////////////////


					//bool cur_condition;
					//
					//if (temp_st.len == cur_term_len&&temp_st.len>2)
					//{
					//	for (int ii = 1; ii < cur_term_len; ii++)
					//	{
					//		cur_condition = true;
					//		for (int jj = 1; jj < cur_term_len; jj++)
					//		{
					//			if (jj == ii)
					//				cur_condition = cur_condition && (temp_st.nums[jj] <= 8);
					//			else
					//				cur_condition = cur_condition && (temp_st.ops[jj]=='z');
					//		}
					//		double f = 1;
					//		if (cur_condition)
					//		{
					//			for (int k = 1; k < cur_term_len - 1; k++)
					//				f *= factor;
					//			final_st.len = 2;
					//			final_st.ops[0] = temp_st.ops[0];
					//			final_st.nums[0] = temp_st.nums[0];
					//			final_st.ops[1] = temp_st.ops[ii];
					//			final_st.nums[1] = temp_st.nums[ii];
					//			for (int l = 1; l <= max_order; l++)
					//				final_st.value[l] = 0;
					//			final_st.value[j] = temp_val*f;
					//			final_st.name = "J";
					//			final_st.name = final_st.name + final_st.ops[0] + final_st.ops[1] + to_string(final_st.nums[0]) + "_" + to_string(final_st.nums[1]);
					//			flag = true;
					//			vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					//			if (it != res.end())
					//				it->value[j] += temp_val*f;
					//			else
					//				res.push_back(final_st);
					//		}
					//	}
					//}

					//////////////////////////////////////////////////////////////////////
					//for sz
					//////////////////////////////////////////////////////////////////////

					/*double f = 1;
					if (temp_st.len == cur_term_len)
					{
					bool flag = (temp_st.nums[0]==0);
					for (int ii = 1; ii < cur_term_len; ii++)
					{
					if (temp_st.ops[ii] != 'z' || temp_st.nums[ii] <= 8)
					{
					flag = false;
					break;
					}
					}
					if (flag)
					{
					for (int k = 1; k < cur_term_len - 1; k++)
					f *= factor;
					final_st.len = 1;
					final_st.ops[0] = temp_st.ops[0];
					final_st.nums[0] = 0;
					for (int l = 1; l <= max_order; l++)
					final_st.value[l] = 0;
					final_st.value[j] = temp_val*f;
					final_st.name = "S";
					final_st.name=final_st.name+ final_st.ops[0] + "0";
					vector<st>::iterator it = find(res.begin(), res.end(), final_st);
					if (it != res.end())
					it->value[j] += temp_val*f;
					else
					res.push_back(final_st);
					}
					}*/

					//////////////////////////////////////////////////////////////////////
					//for long-second terms
					//////////////////////////////////////////////////////////////////////


					bool flag = false;
					/*if (temp_st.len == cur_term_len )
					{
					if (temp_st.nums[0] == 0 && temp_st.nums[1] > 8)
					{
					if (temp_st.ops[0] == 'p'&&temp_st.ops[1] == 'p')
					flag = true;
					if (temp_st.ops[0] == 'p'&&temp_st.ops[1] == 'm')
					flag = true;
					if (temp_st.ops[0] == 'm'&&temp_st.ops[1] == 'p')
					flag = true;
					if (temp_st.ops[0] == 'm'&&temp_st.ops[1] == 'm')
					flag = true;
					if (flag)
					{
					int find_flag=-1;
					for (int lll = 0; lll < long_res.size(); lll++)
					{
					if (long_res[lll].ops[0] == temp_st.ops[0] && long_res[lll].ops[1] == temp_st.ops[1])
					{
					find_flag = lll;
					break;
					}
					}

					if (find_flag != -1)
					{
					if ((temp_st.nums[1] != 14 && temp_st.nums[1] != 18 && temp_st.nums[1] != 22 && temp_st.nums[1] != 10) && (PiPoint == 1))
					long_res[find_flag].value[j] -= temp_val;
					else
					long_res[find_flag].value[j] += temp_val;
					}
					else
					{
					for (int l = 1; l <= max_order; l++)
					temp_st.value[l] = 0;
					if ((temp_st.nums[1] != 14 && temp_st.nums[1] != 18 && temp_st.nums[1] != 22 && temp_st.nums[1] != 10) && (PiPoint == 1))
					temp_st.value[j] = -temp_val;
					else
					temp_st.value[j] = temp_val;
					long_res.push_back(temp_st);
					}

					}

					}
					}*/


					char var[4][2] = { { 'p', 'p' }, { 'p', 'm' }, { 'm', 'p' }, { 'm', 'm' } };

					if (cur_term_len >= 2 && temp_st.len == cur_term_len)
					{

						for (int ii = 0; ii < 4; ii++)
						{
							bool flag = true;
							int  pos = -1;
							if (temp_st.ops[0] == var[ii][0] && temp_st.nums[0] == 0)
							{
								for (int jj = 1; jj < cur_term_len; jj++)
								{
									if (var[ii][1] == temp_st.ops[jj])
									{
										if (pos == -1)
										{
											pos = jj;
										}
										else
										{
											flag = false;
											break;
										}
									}
									else if (temp_st.ops[jj] != 'z')
									{
										flag = false;
										break;
									}
								}
								if (flag && pos != -1)
								{
									stCos cur;
									stCosSer curSer;

									//init
									for (int kk = 0; kk < curSer.NN; kk++)
										curSer.val[kk] = 0;
									cur.series.clear();
									//factor
									double val = 1;
									for (int kk = 0; kk < cur_term_len - 2; kk++)
									{
										val *= factor;
									}

									findCos(m, size, temp_st.nums[pos], curSer.ka, curSer.kb);
									///////////////////////////////////////////////////////
									//temp
									//	if (curSer.ka == 0 && (curSer.kb == 1 || curSer.kb == -1) )//&& temp_st.ops[0] == 'm'&&temp_st.ops[pos] == 'm')
									//end temp
									//////////////////////////////////////////////////////////
									{
										cur.name[0] = temp_st.ops[0];
										cur.name[1] = temp_st.ops[pos];

										curSer.val[j] = val*temp_val;
										vector<stCos>::iterator itC = find(cos_res.begin(), cos_res.end(), cur);
										if (itC != cos_res.end())
										{
											vector<stCosSer>::iterator it2 = find(itC->series.begin(), itC->series.end(), curSer);
											if (it2 != itC->series.end())
											{
												it2->val[j] += curSer.val[j];
											}
											else
											{
												itC->series.push_back(curSer);
											}
										}
										else
										{
											cur.series.push_back(curSer);
											cos_res.push_back(cur);
										}
									}
								}
							}

						}
					}

					//end long-second -terms

					//////////////////////////////////////////////////////////////////////
					//for C and (a0+)(a0)
					//////////////////////////////////////////////////////////////////////

					//////////////////////////////////////////////////////////////////////
					//for C and (a0+)(a0)
					//////////////////////////////////////////////////////////////////////

					if (temp_st.len == cur_term_len&&temp_st.len >= 1 && temp_st.nums[0] == 0)
					{
						flag = true;
						for (int ii = 0; ii < temp_st.len; ii++)
						{
							if (temp_st.ops[ii] != 'z')
							{
								flag = false;
								break;
							}
						}
						if (flag)
						{
							double f = 1;
							for (int pp = 0; pp < temp_st.len - 1; pp++)
								f *= factor;
							c_res.value[j] += (temp_val * f *factor / temp_st.len);
							a0a0.value[j] += temp_val*f;

						}
					}


				}
			}

			cur.close();

		}
		fname.str("");
		fname << "Results\\res_";
		if (cur_term_len != 2)
			fname << points[i] << "_" << max_order << "_" << cur_term_len << ".txt";
		else
		{
			if (PiPoint == 1)
				fname << points[i] << "_" << max_order << "_" << cur_term_len << "__(P,P).txt";
			else
				fname << points[i] << "_" << max_order << "_" << cur_term_len << "__(0,0).txt";
		}
		ofstream out;
		bool fl = false;
		if (fl)
		{
			out.open(fname.str(), ios::out);
			out << "C" << cur_term_len << "={";
			for (int k = 1; k <= max_order; k++)
			{
				out << c_res.value[k];
				if (k != max_order)
					out << ",";
			}
			out << "}\n";

			out << "a0a0" << cur_term_len << "={";
			for (int k = 1; k <= max_order; k++)
			{
				out << a0a0.value[k];
				if (k != max_order)
					out << ",";
			}
			out << "}\n";
			for (int j = 0; j < res.size(); j++)
			{
				//if (res[j].name[0] == 'S' || res[j].nums[1] <=2)
				if (res[j].name[0] == 'S' || res[j].nums[1] == 1 || res[j].nums[1] == 2)
				{
					out << res[j].name << "={";
					for (int k = 1; k <= max_order; k++)
					{
						out << res[j].value[k];
						if (k != max_order)
							out << ",";
					}
					out << "}\n";
				}


			}
			for (int j = 0; j < long_res.size(); j++)
			{
				out << "J" << long_res[j].ops[0] << long_res[j].ops[1] << "={";
				for (int k = 1; k <= max_order; k++)
				{
					out << long_res[j].value[k];
					if (k != max_order)
						out << ",";
				}

				out << "}\n";
			}

			
		}
		out.close();
		fname.str("");
		fname << "Results\\res_" << points[i] << "_" << max_order << "_" << cur_term_len << "_pair.txt";
		out.open(fname.str(), ios::out);
		for (int i = 0; i < cos_res.size(); i++)
		{
			
			out << "a" << cos_res[i].name[0] << "a" << cos_res[i].name[1] << cur_term_len<< "=";
			bool first = true;
			for (int j = 0; j < cos_res[i].series.size(); j++)
			{
				if (cos_res[i].series[j].kb > 0 || (cos_res[i].series[j].kb == 0 && cos_res[i].series[j].ka > 0))
				{
					if (!first)
						out << "+";
					else
						first = false;
					out << "{";
					for (int k = 1; k <= max_order; k++)
					{
						out << cos_res[i].series[j].val[k];
						if (k != max_order)
							out << ",";
					}

					out << "}*Cos[ka*" << cos_res[i].series[j].ka << "+kb*" << cos_res[i].series[j].kb << "]";
					
						
				}
				

			}
			out << ";\n";
		}
		out.close();
	}
	
	return 0;
}


///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// 9 Collect Third Terms.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
//#include <fstream>
//#include <iostream>
//#include <string>
//#include <vector>
//#include <sstream>
//#include <cmath>
//#include <algorithm>
//using namespace std;
//
//const string delim = "\\";
//const string out_res = "results";
//
//struct st
//{
//	string name;
//	double value;
//	bool operator==(st r)
//	{
//		if (name.compare(r.name) == 0)
//			return true;
//		else
//			return false;
//	};
//	/*bool short_compare(st r)
//	{
//	string n1, n2;
//	n1 = name.substr(0, name.length - 1);
//	n2 = r.name.substr(0, r.name.length - 1);
//	if (n1.compare(n2)==0)
//	return true;
//	else
//	}
//	};*/
//
//	vector<st> res;
//	int _tmain(int argc, _TCHAR* argv[])
//	{
//		vector<string> points;
//		ifstream config("config.txt", ios::in);
//		int num_points, order;
//		config >> num_points;
//		config >> order;
//		ifstream fpoints("points.txt", ios::in);
//		string s, tmp_s;
//		for (int i = 0; i < num_points; i++)
//		{
//			getline(fpoints, s);
//			points.push_back(s);
//		}
//		fpoints.close();
//		ostringstream fname;
//		st temp;
//		bool flag;
//		ifstream valueFile;
//		for (int i = 0; i < num_points; i++)
//		{
//			int factor;
//			double sz;
//			fname.str("");
//			fname << "d:\\results\\resumm\\s00\\sz0_" << order << "_" << points[i] << ".txt";
//			ifstream szfile(fname.str(), ios::in);
//			while (!szfile.eof())
//			{
//				szfile >> sz;
//			}
//			szfile.close();
//			if (sz > 0)
//				factor = -1;
//			else
//				factor = 1;
//			cout << factor << "\n";
//			fname.str("");
//			fname << points[i] << "_third_names.txt";
//			ifstream cur(fname.str(), ios::in);
//			res.clear();
//			while (!cur.eof())
//			{
//				getline(cur, s);
//				istringstream iss;
//				iss.str(s);
//				iss >> tmp_s;
//				flag = false;
//				if ((s[2] == 'z') && (s[3] != 'z'))
//				{
//					ifstream fn;
//					fname.str("");
//					fname << points[i] << "_third_names.txt";
//					temp.name = "J" + s[1] + s[3] + s[4] + s[6];
//					iss >> temp.value;
//					temp.value *= factor*0.5;
//					flag = true;
//					vector<st>::iterator it = find(res.begin(), res.end(), temp);
//					if (it != res.end())
//						it->value += temp.value;
//					else
//						res.push_back(temp);
//				}
//				if ((s[3] == 'z') && (s[2] != 'z'))
//				{
//					temp.name = "J" + s[1] + s[2] + s[4] + s[5];
//					iss >> temp.value;
//					temp.value *= factor*0.5;
//					flag = true;
//					vector<st>::iterator it = find(res.begin(), res.end(), temp);
//					if (it != res.end())
//						it->value += temp.value;
//					else
//						res.push_back(temp);
//				}
//			}
//
//			cur.close();
//			fname.str("");
//			fname << "res_" << points[i] << "_" << order << ".txt";
//			ofstream out(fname.str(), ios::out);
//			for (int j = 0; j < res.size(); j++)
//			{
//				out << res[j].name << " " << res[j].value;
//			}
//			out.close();
//		}
//
//		return 0;
//	}
//
//
//
//
//
