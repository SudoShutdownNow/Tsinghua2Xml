#include <iostream>
#include <string.h>
#pragma warning(disable: 4996)

using namespace std;

struct label {
	float xmin;
	float ymin;
	float xmax;
	float ymax;
	char labelname[30];
};
struct file {
	int contain;//���ļ��������ٸ���ǩ
	char filename[10];//���ļ�������
	label label[100];//���б�ǩ

}nowfile;
int LoadFile(FILE* fp, char* buffer)
{

	if (fread(buffer, 9999, 1, fp) == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}

int SeekPath(char* buffer, char*& p, char*& next)
{
	p = strstr(buffer, "path");
	if (p == NULL)
	{
		return 0;
	}
	buffer = p + sizeof("path");
	next = strstr(buffer, "path");
	if (next == NULL)
		next = buffer + sizeof(buffer);
	buffer = p; //buffer return position

	if (strstr(buffer, "imgs") == NULL)
	{
		//system("pause");
	}
	return (next - p);


}

void spliter(char* ppath, char* nextpath)//������path���֮������ݷָ�
{
	char* seeker, *operater;
	
	seeker = strstr(ppath, "\/");
	seeker++;

	//Ѱ�Ҳ�ת¼path
	operater = nowfile.filename;
	for (int i = 0; *seeker != '\.'; i++)
	{
		
		*operater = *seeker;

		seeker++;
		operater++;
	}
	*operater = 0;

	//��λcategoryֱ������nextpath
	int lc = 0;//labelcounter
	while (1)
	{
		seeker = strstr(ppath, "category");
		if (seeker > nextpath)
		{
			break;
		}
		else if (seeker == NULL)
		{
			break;
		}
		while (*seeker != '\:')//��ǰ�ƶ�ֱ��������
		{
			seeker++;
		}
		while (*seeker != '\"')//��ǰ�ƶ�ֱ��������
		{
			seeker++;
		}
		seeker++;

		
		if (*seeker == 'p')
		{
			strcpy(nowfile.label[lc].labelname, "prohibitory");
		}
		else if (*seeker == 'w')
		{
			strcpy(nowfile.label[lc].labelname, "warning");
		}
		else if (*seeker == 'i')
		{
			strcpy(nowfile.label[lc].labelname, "mandatory");
		}
		else
		{
			strcpy(nowfile.label[lc].labelname, "unknown");
		}

		//��ʼת¼����
		//ת¼xmin
		char temp[30];
		char* intbuffer = temp;
		seeker = strstr(ppath, "xmin");
		if (seeker > nextpath || seeker == NULL)
		{
			goto endsplit;
		}
		while (*seeker != '\:')
		{
			seeker++;
		}
		seeker += 2;
		while (*seeker != '\,')
		{
			*intbuffer = *seeker;
			intbuffer++;
			seeker++;
		}
		*intbuffer = '\0';
		sscanf(temp, "%f", &nowfile.label[lc].xmin);
		//delete intbuffer;

		//ת¼ymin
		//intbuffer = new char[15];
		intbuffer = temp;
		seeker = strstr(ppath, "ymin");
		if (seeker > nextpath || seeker == NULL)
		{
			goto endsplit;
		}
		while (*seeker != '\:')
		{
			seeker++;
		}
		seeker += 2;
		while (*seeker != '\,')
		{
			*intbuffer = *seeker;
			intbuffer++;
			seeker++;
		}
		*intbuffer = '\0';
		sscanf(temp, "%f", &nowfile.label[lc].ymin);

		//ת¼xmax
		//intbuffer = new char[15];
		intbuffer = temp;
		seeker = strstr(ppath, "ymax");
		if (seeker > nextpath || seeker == NULL)
		{
			goto endsplit;
		}
		while (*seeker != '\:')
		{
			seeker++;
		}
		seeker += 2;
		while (*seeker != '\,')
		{
			*intbuffer = *seeker;
			intbuffer++;
			seeker++;
		}
		*intbuffer = '\0';
		sscanf(temp, "%f", &nowfile.label[lc].ymax);

		//ת¼ymax
		//intbuffer = new char[15];
		intbuffer = temp;
		seeker = strstr(ppath, "xmax");
		if (seeker > nextpath || seeker == NULL)
		{
			goto endsplit;
		}
		while (*seeker != '\:')
		{
			seeker++;
		}
		seeker += 2;
		while (*seeker != '\}')
		{
			*intbuffer = *seeker;
			intbuffer++;
			seeker++;
		}
		*intbuffer = '\0';
		sscanf(temp, "%f", &nowfile.label[lc].xmax);


		endsplit:
		cout << "\t" << nowfile.label[lc].labelname <<" xmin="<<nowfile.label[lc].xmin << " ymin=" << nowfile.label[lc].ymin << " xmax=" << nowfile.label[lc].xmax << " ymax=" << nowfile.label[lc].ymax << endl;
		lc++;
		nowfile.contain = lc;
		ppath = seeker;
	}


}
void outputxml(FILE* fp)
{
	
	char outputfile[20];
	sprintf(outputfile, "%s.xml", nowfile.filename);

	fp = fopen (outputfile, "w");
	fprintf(fp, "<annotation>\n");
	fprintf(fp, "\t<filename>%s.jpg<\/filename>\n",nowfile.filename);

	fprintf(fp, "\t<source>\n");
	fprintf(fp, "\t\t<database>Unknown<\/database>\n");
	fprintf(fp, "\t<\/source>\n");

	fprintf(fp, "\t<size>\n");
	fprintf(fp, "\t\t<width>2048<\/width>\n");
	fprintf(fp, "\t\t<height>2048<\/height>\n");
	fprintf(fp, "\t\t<depth>3<\/depth>\n");
	fprintf(fp, "\t<\/size>\n");

	fprintf(fp, "\t<segmented>0<\/segmented>\n");

	for (int i = 0; i < nowfile.contain; i++)
	{
		fprintf(fp, "\t<object>\n");


		fprintf(fp, "\t\t<name>%s<\/name>\n",nowfile.label[i].labelname);
		fprintf(fp, "\t\t<pose>Unsprcified<\/pose>\n");
		fprintf(fp, "\t\t<truncated>0<\/truncated>\n");
		fprintf(fp, "\t\t<difficult>0<\/difficult>\n");
		fprintf(fp, "\t\t<bndbox>\n");
		fprintf(fp, "\t\t\t<xmin>%.2f<\/xmin>\n",nowfile.label[i].xmin);
		fprintf(fp, "\t\t\t<ymin>%.2f<\/ymin>\n", nowfile.label[i].ymin);
		fprintf(fp, "\t\t\t<xmax>%.2f<\/xmax>\n", nowfile.label[i].xmax);
		fprintf(fp, "\t\t\t<ymax>%.2f<\/ymax>\n", nowfile.label[i].ymax);
		fprintf(fp, "\t\t<\/bndbox>\n");


		fprintf(fp, "\t<\/object>\n");
	}

	fprintf(fp, "<\/annotation>\n");
	fclose(fp);
	nowfile.contain = 0;
}

int main()
{
	int countpath = 1;
	int loaded = 0;

	char* buffer=new char[10000];
	FILE* fp;
	FILE* target = NULL;//ת���������ļ�ָ��
	fp = fopen("annotations.json", "r");

	char* ppath = new char;//��ǰpath����λ��ָ��
	char* nextpath = new char;//��һ��path����λ��ָ��
	

	int length,empty =0;
	int total=0;


	while (LoadFile(fp, buffer) != 0)
	{
		length = SeekPath(buffer, ppath, nextpath);
		total += length;
		if (length == 0 || length == 1)
			break;
		empty = ppath - buffer;
		loaded = strlen(buffer);

		spliter(ppath, nextpath);
		outputxml(target);



		cout << "the label langth " << length <<" total " << total <<" filename is "<<nowfile.filename << endl;
		fseek(fp, -( loaded - length - empty), SEEK_CUR);

	}
	fclose(fp);
	//�ļ������󣬲�������ȡ�ļ�����������ʣ��ı�ǩ
	while (1)
	{
		length = SeekPath(buffer, ppath, nextpath);
		total += length;
		if (length == 0 || length == 1)
			break;
		empty = ppath - buffer;
		loaded = strlen(buffer);

		spliter(ppath, nextpath);
		outputxml(target);

		cout << "the label langth " << length << " total " << total << " filename is " << nowfile.filename << endl;
		
		//pathָ����ǰ�ƶ�
		ppath += sizeof("path\"");
		buffer = ppath;
		nextpath += sizeof("path\"");
	}

	cout << "��ȫ��������ɣ�";
	system("pause");
}