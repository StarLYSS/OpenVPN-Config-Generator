#include<stdio.h>
#include<stdlib.h>
#include<io.h>

char server_ip[25];
int port_start,port_gap,port,i;
FILE* server_config, * client_config, * server_cert,*client_cert, * client_key;


int main() {
MainMenu:system("cls");
	UserInterface();
	server();
	client();
	system("explorer config\\");
	system("pause");
	goto MainMenu;
}

int UserInterface(){
	if (access("config", 0)) {
		system("mkdir config");
	}
	if (access("save", 0)) {
		system("mkdir save");
	}
	printf("�����������������ip��ַ��\n");
	scanf("%s", server_ip);
	Input:printf("��������ʼ�˿ںţ�\n");
	scanf("%d", &port_start);
	printf("������˿ںż����\n");
	scanf("%d", &port_gap);
	if (port_start < 10000 || port_start>65535) {
		printf("��ʼ�˿ں����벻�Ϸ���\n");
		goto Input;
	}
	if ((server_cert = fopen("save\\server.cert", "r")) == NULL) {
		server_cert = fopen("save\\server.cert", "w");
		fclose(server_cert);
	}
	if ((client_cert = fopen("save\\client.cert", "r")) == NULL) {
		client_cert = fopen("save\\client.cert", "w");
		fclose(client_cert);
	}
	if ((client_key = fopen("save\\client.key", "r")) == NULL) {
		client_key = fopen("save\\client.key", "w");
		fclose(client_key);
	}
	printf("���ڵ��������е��������֤�飨���Դ�֮ǰ�����������ļ��е������������뵼�룩. . .\n");
	system("notepad save\\server.cert");
	printf("���ڵ��������е���ͻ���֤�飨���Դ�֮ǰ�����������ļ��е����ڶ������뵼�룩. . .\n");;
	system("notepad save\\client.cert");
	printf("���ڵ��������е���ͻ���˽Կ�����Դ�֮ǰ�����������ļ������һ�����뵼�룩. . .\n");
	system("notepad save\\client.key");
	printf("���ݵ�����ɣ��������������ļ�. . .\n");
	return 0;
}

int server() {
	server_config = fopen("config\\server_config.txt", "w");
	for (i = 0, port = port_start; i < 64; port = port + port_gap, i++) {
		if (port <= 65535)fprintf(server_config, "%d,", port);
		else {
			printf("���ڶ˿ںŴ�С������Զ�ȡ��Сֵ10001��\n");
			port = 10001;
			i = i - 1;
		}
	}
	fclose(server_config);
	printf("�������������ļ������ɣ�\n");
	return 0;
}

int client() {
	client_config = fopen("config\\client_config.ovpn", "w");
	fprintf(client_config, "dev tun\n");
	fprintf(client_config, "proto udp\n");
	fprintf(client_config, "remote-random\n");
	fprintf(client_config, "cipher AES-128-CBC\n");
	fprintf(client_config, "auth SHA1\n");
	fprintf(client_config, "resolv-retry infinite\n");
	fprintf(client_config, "nobind\n");
	fprintf(client_config, "persist-key\n");
	fprintf(client_config, "persist-tun\n");
	fprintf(client_config, "client\n");
	fprintf(client_config, "verb 3\n");
	fprintf(client_config, "auth-user-pass\n");
	for (i = 0, port = port_start; i < 64; port = port + port_gap, i++) {
		if (port <= 65535)fprintf(client_config, "remote %s %d\n", server_ip,port);
		else {
			printf("���ڶ˿ںŴ�С������Զ�ȡ��Сֵ10001��\n");
			port = 10001;
			i = i - 1;
		}
	}
	fclose(client_config);
	client_config = fopen("config\\client_config.ovpn", "a");
	fprintf(client_config, "\n\n");
	fclose(client_config);
	system("type save\\server.cert>>config\\client_config.ovpn");
	client_config = fopen("config\\client_config.ovpn", "a");
	fprintf(client_config, "\n\n");
	fclose(client_config);
	system("type save\\client.cert>>config\\client_config.ovpn");
	client_config = fopen("config\\client_config.ovpn", "a");
	fprintf(client_config, "\n\n");
	fclose(client_config);
	system("type save\\client.key>>config\\client_config.ovpn");
	client_config = fopen("config\\client_config.ovpn", "a");
	fprintf(client_config, "\n\n");
	fclose(client_config);
	printf("�ͻ��˶������ļ������ɣ�\n");
	return 0;
}