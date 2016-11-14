//������������Ӧ��
// ������    2016��11��10��14:44:28

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

typedef struct {
	int weight;		//���Ȩֵ
	int parent, lchild, rchild;//˫�ס����ӡ��Һ��ӵ��±�
}HTNode, *HuffmanTree;

typedef char **HuffmanCode;//��̬��������洢�����������


						   //��HT��ǰn���������Ȩֵ��С�����������±꣬�洢��s1,s2��
void select(HuffmanTree &HT, int n, int &s1, int &s2)
{
	/*
	s1 = 0;
	s2 = 0;
	for (int i = 1; i <= n; i++)
	{
	if (HT[i].parent == 0)
	{
	if (s1 == 0)
	s1 = i;
	else
	if (HT[i].weight < HT[s1].weight)
	{
	//		s2 = s1;
	s1 = i;
	}
	}
	}
	HT[s1].parent = 1;
	for (int i = 1; i <= n; i++)
	{
	if (HT[i].parent == 0)
	{
	if (s2 == 0)
	s2 = i;
	else
	if (HT[i].weight < HT[s2].weight)
	{
	//		s2 = s1;
	s2 = i;
	}
	}
	}
	*/
	s1 = 0;
	s2 = 0;
	for (int i = 1; i <= n; i++)
	{
		if (HT[i].parent == 0)
		{
			if (s1 == 0)
				s1 = i;
			else if (s2 == 0)
			{
				s2 = i;
				if (HT[s1].weight > HT[s2].weight)
				{
					int p = s1;
					s1 = s2;
					s2 = p;
				}
			}
			else
			{
				if (HT[i].weight < HT[s2].weight)
					if (HT[i].weight < HT[s1].weight)
					{
						s2 = s1;
						s1 = i;
					}
					else
						s2 = i;

			}
		}
	}
}

//�������������������ĿΪn
void createHuffmanTree(HuffmanTree &HT, int n, int *weight)
{
	if (n <= 1)
		return;
	int m = 2 * n - 1;//���������Ľ�����Ϊ2n - 1
	HT = new HTNode[m + 1];//���� m + 1 ����㣬��һ����㲻ʹ��
	for (int i = 1; i <= m; i++)//�����н���˫�ס����Һ����±��ʼ��Ϊ0
	{
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for (int i = 1; i <= n; i++)//����n��Ҷ�ӽ���Ȩֵ
	{
		HT[i].weight = weight[i];
	}

	//������������
	int s1, s2;
	for (int i = n + 1; i <= m; i++)
	{
		//�ڸý���ǰ����Ȩֵ��С�����������±�ֱ�洢��s1,s2��
		select(HT, i - 1, s1, s2);
		//���ҵ���Ȩֵ��С����������˫���±���Ϊi
		HT[s1].parent = i;
		HT[s2].parent = i;
		//��i�������Һ��ӷֱ���Ϊs1,s2
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;//i����ȨֵΪ���Һ���s1��s2��Ȩֵ֮��
	}
}

//��Ҷ�ӵ���������ÿ���ַ��Ĺ��������룬�洢�ڱ����HC��
void createHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n)
{
	HC = new char*[n + 1];
	char *cd = new char[n];
	cd[n - 1] = '\0';
	int start, par, m;
	for (int i = 1; i <= n; i++)
	{
		start = n - 1;
		m = i;//mΪ��ǰ����±�
		par = HT[m].parent;//parΪm��˫�׽���±�
		while (par != 0)
		{
			--start;
			if (HT[par].lchild == m)	//m��par������
				cd[start] = '0';
			else                        //m��par���Һ���
				cd[start] = '1';
			m = par;
			par = HT[m].parent;
		}
		HC[i] = new char[n - start];
		strcpy(HC[i], &cd[start]);
	}
	delete cd;
}
//���룬���ù����������ԭ���ַ�������
int bianMa(HuffmanCode HC, char *ziFu, string yuanMa, string &result)
{
	bool flag;
	int len = yuanMa.length();
	for (int i = 0; i < len; i++)
	{
		flag = false;
		int j;
		for (j = 1; ziFu[j] != '\0'; j++)
			if (ziFu[j] == yuanMa[i])
			{
				flag = true;
				break;
			}
		if (!flag)
		{

			return 0;
		}
		result.append(HC[j]);
	}
	return 1;
}
//���룬���ù�����������������
int yiMa(HuffmanTree HT, int n, char *ziFu, string yuanMa, string &result)
{
	int i;
	int len = yuanMa.length();
	int root;
	root = 2 * n - 1;
	i = 0;
	int p = root;
	while (true)
	{
		if (HT[p].lchild == 0 && HT[p].rchild == 0)
		{
			result.append(1, ziFu[p]);
			p = root;
		}
		else if (i == len)
			return 0;
		if (i >= len)
			break;
		if (yuanMa[i] == '0')
			p = HT[p].lchild;
		else if (yuanMa[i] == '1')
			p = HT[p].rchild;
		else
			return 0;
		i++;
	}
	return 1;
}

void main()
{
	HuffmanTree HT = NULL;
	int n;
	char *ziFu = NULL;
	int *weight = NULL;
	HuffmanCode HC = NULL;
	/*
	����������
	��������8
	�ַ��Ͷ�Ӧ��Ȩֵ��a 5 b 29 c 7 d 8 e 14 f 23 g 3 h 11   �����Կ��Ը���ճ����
	���룺ceaghbd   ��Ӧ�ı���Ϊ��   111011000010000001101111
	*/
	char ch = 'y';
	int b;
	while (ch == 'y')
	{
		cout << endl << "\t\t1��������������" << endl;
		cout << "\t\t2����������������" << endl;
		cout << "\t\t3���������������" << endl;
		cout << "\t\t4���������������" << endl;
		cout << "\t\t5������" << endl;
		cout << "\t\t6������" << endl;
		cout << "\t\t0���˳�" << endl;
		cout << "�����룺";
		cin >> b;
		switch (b)
		{
		case 1://�����������
		{
			ifstream ziFuAndWeight("ziFuAndWeight.txt");
			ziFuAndWeight >> n;
			ziFu = new char[n + 1];
			weight = new int[n + 1];

			//�����ַ��Ͷ�Ӧ��Ȩֵ
			for (int i = 1; i <= n; i++)
				ziFuAndWeight >> ziFu[i] >> weight[i];
			ziFuAndWeight.close();
			//������������
			createHuffmanTree(HT, n, weight);
			cout << "��������������" << endl;
			break;
		}
		case 2:
			//��������������
			if (HT)
			{
				createHuffmanCode(HT, HC, n);
				cout << "���������빹�����" << endl;
			}
			else
				cout << "��������û�й������޷��������������룡" << endl;
			break;
		case 3:
			//�������������
			if (HT)
			{
				cout << "���\tȨֵ\t˫��\t��\t��" << endl;
				for (int i = 1; i <= 2 * n - 1; i++)
				{
					cout << i << "\t" << HT[i].weight << "\t" << HT[i].parent << "\t" << HT[i].lchild << "\t" << HT[i].rchild << endl;
				}
			}
			else
				cout << "��������δ�������޷��������������" << endl;
			break;
		case 4:
			//�������������
			if (HC)
				for (int i = 1; i <= n; i++)
					cout << ziFu[i] << " : " << HC[i] << endl;
			else
				cout << "����������δ�������޷�������������룡" << endl;
			break;
		case 5:
			//����
			if (HC)
			{
				string bianMaYuanFile,yuanMa,bianMa_result;
				cout << "��������Ҫ������ַ������ļ�����" ;
				cin >> bianMaYuanFile;
				ifstream bianMaInput(bianMaYuanFile);
				char ch;
				while (bianMaInput.get(ch))
					yuanMa.append(1, ch);
				bianMaInput.close();
				if (bianMa(HC, ziFu, yuanMa, bianMa_result) == 1)
				{
					cout << yuanMa << " ��Ӧ�ı��� " << bianMa_result << endl;
					ofstream bianMaOutput("bianMaOutPut.txt");
					bianMaOutput << bianMa_result;
					bianMaOutput.close();
				}
				else
					cout << "ԭ���д�" << endl;
			}
			else
				cout << "����������δ�������޷����룡" << endl;
			break;
		case 6:
			//����
			if (HT)
			{
				string yiMaYuanFile,yuanMa,yiMa_result;
				cout << "����������Ķ������ַ������ļ�����";
				cin >> yiMaYuanFile;
				ifstream yiMaInput(yiMaYuanFile);
				char ch;
				while (yiMaInput.get(ch))
					yuanMa.append(1, ch);
				yiMaInput.close();
				if (yiMa(HT, n, ziFu, yuanMa, yiMa_result) == 1)
				{
					cout << yuanMa << "��Ӧ��ԭ�ַ���Ϊ �� " << yiMa_result << endl;
					ofstream yiMaOutput("yiMaOutput.txt");
					yiMaOutput << yiMa_result;
					yiMaOutput.close();
				}
				else
					cout << "�����ַ����д�" << endl;
				break;
			}
			else
				cout << "��������Ϊ�������޷����룡" << endl;
			break;
		case 0:
			ch = 'n'; break;
		default:
			cout << "�������" << endl;
			break;
		}
	}
}