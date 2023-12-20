#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc,char *argv[])
{
    int sock;
    struct sockaddr_in clien;
    char *servIP;
    servIP=argv[1];
    unsigned int port_number;
    printf("IPv4:%s\n",servIP);
    for(port_number=0;port_number<=65535;port_number++)
    {
        sock=0;
        if((sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
        {
            perror("socket failed");
            exit(1);
        }
        memset(&clien,0x00,sizeof(clien));
        clien.sin_family=AF_INET;
        clien.sin_addr.s_addr=inet_addr(servIP);
        clien.sin_port=htons(port_number);
        if(connect(sock,(struct sockaddr*)&clien,sizeof(clien))<0)
        {
            close(sock);
            continue;
        }
        printf("tcp/%d\n",port_number);
    }
    close(sock);
    return 0;
}