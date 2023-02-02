
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include "base64.h"
#include "para.h"
#include "time.h"

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>

#define BUF_LEN 1024
#define BOUNDARY "boundary"
#define imagePath "/home/e5470/Pictures/anh.png"
#define audioPath "/home/e5470/Downloads/audio.mp3"
#define videoPath "/home/e5470/Downloads/video.mp4"

char *MailHeader(const char *from, const char *to, const char *subject, const char *mime_type, const char *charset)
{

  time_t now;
  time(&now);
  char *app_brand = "Codevlog Test APP";
  char *mail_header = NULL;
  char date_buff[26];
  char Branding[6 + strlen(date_buff) + 2 + 10 + strlen(app_brand) + 1 + 1];
  char Sender[6 + strlen(from) + 1 + 1];
  char Recip[4 + strlen(to) + 1 + 1];
  char Subject[8 + 1 + strlen(subject) + 1 + 1];
  char mime_data[13 + 1 + 3 + 1 + 1 + 13 + 1 + strlen(mime_type) + 1 + 1 + 8 + strlen(charset) + 1 + 1 + 2];

  strftime(date_buff, (33), "%a , %d %b %Y %H:%M:%S", localtime(&now));

  sprintf(Branding, "DATE: %s\r\nX-Mailer: %s\r\n", date_buff, app_brand);
  sprintf(Sender, "FROM: %s\r\n", from);
  sprintf(Recip, "To: %s\r\n", to);
  sprintf(Subject, "Subject: %s\r\n", subject);
  sprintf(mime_data, "MIME-Version: 1.0\r\nContent-type: %s; boundary=%s\r\n\r\n", mime_type, BOUNDARY);

  int mail_header_length = strlen(Branding) + strlen(Sender) + strlen(Recip) + strlen(Subject) + strlen(mime_data) + 10;

  mail_header = (char *)malloc(mail_header_length * sizeof(char));

  memcpy(&mail_header[0], &Branding, strlen(Branding));
  memcpy(&mail_header[0 + strlen(Branding)], &Sender, strlen(Sender));
  memcpy(&mail_header[0 + strlen(Branding) + strlen(Sender)], &Recip, strlen(Recip));
  memcpy(&mail_header[0 + strlen(Branding) + strlen(Sender) + strlen(Recip)], &Subject, strlen(Subject));
  memcpy(&mail_header[0 + strlen(Branding) + strlen(Sender) + strlen(Recip) + strlen(Subject)], &mime_data, strlen(mime_data));
  return mail_header;
}

int main(int argc, char **argv)
{
  BIO *obj_bio = NULL;
  BIO *obj_out = NULL;
  const SSL_METHOD *method;
  SSL_CTX *ctx;
  SSL *ssl;
  int connceted_fd = 0;
  int ret, i;

  OpenSSL_add_all_algorithms();
  ERR_load_BIO_strings();
  ERR_load_crypto_strings();
  SSL_load_error_strings();

  obj_bio = BIO_new(BIO_s_file());
  obj_out = BIO_new_fp(stdout, BIO_NOCLOSE);

  if (SSL_library_init() < 0)
  {
    BIO_printf(obj_out, "OpenSSL not initialize");
  }
  else
  {
    method = SSLv23_client_method();
    if ((ctx = SSL_CTX_new(method)) == NULL)
    {
      BIO_printf(obj_out, "OpenSSL context not initialize");
    }
    else
    {
      SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2);
      ssl = SSL_new(ctx);
      connceted_fd = ConnectToServer(smtp_server_url);
      if (connceted_fd != 0)
      {
        BIO_printf(obj_out, "Connected Successfully");
        SSL_set_fd(ssl, connceted_fd);
        if (SSL_connect(ssl) != 1)
        {
          BIO_printf(obj_out, "SLL session not created");
        }
        else
        {
          char *header = MailHeader(MAIL_HEADER_FROM, MAIL_HEADER_TO, "Hello Its a test Mail from DevHuGo", "multipart/mixed", "US-ASCII");

          int recvd = 0;
          const char recv_buff[4768];
          int sdsd;
          sdsd = SSL_read(ssl, recv_buff + recvd, sizeof(recv_buff) - recvd);
          recvd += sdsd;

          char buff[1000];
          strcpy(buff, "EHLO "); //"EHLO sdfsdfsdf.com\r\n"
          strcat(buff, domain_name);
          strcat(buff, "\r\n");
          SSL_write(ssl, buff, strlen(buff));
          sdsd = SSL_read(ssl, recv_buff + recvd, sizeof(recv_buff) - recvd);
          recvd += sdsd;

          char _cmd2[1000];
          strcpy(_cmd2, "AUTH LOGIN\r\n");
          int dfdf = SSL_write(ssl, _cmd2, strlen(_cmd2));
          sdsd = SSL_read(ssl, recv_buff + recvd, sizeof(recv_buff) - recvd);
          recvd += sdsd;

          char _cmd3[1000];
          Base64encode(&_cmd3, UID, strlen(UID));
          strcat(_cmd3, "\r\n");
          SSL_write(ssl, _cmd3, strlen(_cmd3));
          sdsd = SSL_read(ssl, recv_buff + recvd, sizeof(recv_buff) - recvd);
          recvd += sdsd;

          char _cmd4[1000];
          Base64encode(&_cmd4, PWD, strlen(PWD));
          strcat(_cmd4, "\r\n");
          SSL_write(ssl, _cmd4, strlen(_cmd4));
          sdsd = SSL_read(ssl, recv_buff + recvd, sizeof(recv_buff) - recvd);
          recvd += sdsd;

          char _cmd5[1000];
          strcpy(_cmd5, "MAIL FROM: ");
          strcat(_cmd5, FROM);
          strcat(_cmd5, "\r\n");
          SSL_write(ssl, _cmd5, strlen(_cmd5));
          char skip[1000];
          sdsd = SSL_read(ssl, skip, sizeof(skip));

          char _cmd6[1000];
          strcpy(_cmd6, "RCPT TO: ");
          strcat(_cmd6, TO); //
          strcat(_cmd6, "\r\n");
          SSL_write(ssl, _cmd6, strlen(_cmd6));
          sdsd = SSL_read(ssl, recv_buff + recvd, sizeof(recv_buff) - recvd);
          recvd += sdsd;

          char _cmd7[1000];
          strcpy(_cmd7, "DATA\r\n");
          SSL_write(ssl, _cmd7, strlen(_cmd7));
          sdsd = SSL_read(ssl, recv_buff + recvd, sizeof(recv_buff) - recvd);
          recvd += sdsd;

          SSL_write(ssl, header, strlen(header));
          // char _cmd8[1000];
          // strcpy(_cmd8, "I own CodeVlog you tube channel");
          // SSL_write(ssl, _cmd8, sizeof(_cmd8));

          FILE *fp = fopen(imagePath, "rb");
          if (!fp)
          {
            perror("fopen");
            return 1;
          }
          fseek(fp, 0, SEEK_END);
          int size = ftell(fp);
          fseek(fp, 0, SEEK_SET);
          char *base64_image = (char *)calloc(size, 1);
          size_t image_len = fread(base64_image, 1, size, fp);
          printf("\nImage size: %d\n", image_len);
          fclose(fp);

          char *encoded_image = (char *)calloc(image_len * 2, 1);
          size_t encoded_len = Base64encode(encoded_image, base64_image, image_len);
          printf("Encoded image length: %d\n", encoded_len);
          char message[1024];

          // Add image file attachment
          snprintf(message, sizeof(message), "--%s\r\n"
                                             "Content-Type: text/plain\r\n"
                                             "Content-Disposition: inline\r\n\r\n"
                                             "Hello,\r\n"
                                             "This is a sample MIME Multipart message.\r\n",
                   BOUNDARY);

          SSL_write(ssl, message, strlen(message));

          char image_header[1024];
          snprintf(image_header, sizeof(image_header), "--%s\r\n"
                                                       "Content-Type: image/jpeg\r\n"
                                                       "Content-Transfer-Encoding: base64\r\n"
                                                       "Content-Disposition: attachment; filename=anh.png\r\n\r\n",
                   BOUNDARY);
          SSL_write(ssl, image_header, strlen(image_header));

          SSL_write(ssl, encoded_image, strlen(encoded_image));

          free(base64_image);
          base64_image = NULL;
          free(encoded_image);
          encoded_image = NULL;

          char audio_header[1024];
          snprintf(audio_header, sizeof(audio_header), "\r\n--%s\r\n"
                                                       "Content-Type: audio/mpeg\r\n"
                                                       "Content-Transfer-Encoding: base64\r\n"
                                                       "Content-Disposition: attachment; filename=audio.mp3\r\n\r\n",
                   BOUNDARY);

          SSL_write(ssl, audio_header, strlen(audio_header));

          // Add audio file attachment
          fp = fopen(audioPath, "rb");
          if (!fp)
          {
            perror("fopen");
            return 1;
          }
          fseek(fp, 0, SEEK_END);
          size = ftell(fp);
          fseek(fp, 0, SEEK_SET);
          char *base64_audio = (char *)calloc(size, 1);
          size_t audio_len = fread(base64_audio, 1, size, fp);
          printf("\nAudio size: %d\n", audio_len);
          fclose(fp);

          char *encoded_audio = (char *)calloc(audio_len * 2, 1);
          size_t audio_encoded_len = Base64encode(encoded_audio, base64_audio, audio_len);
          printf("Encoded audio length: %d\n", audio_encoded_len);

          SSL_write(ssl, encoded_audio, strlen(encoded_audio));
          free(encoded_audio);
          encoded_audio = NULL;
          free(base64_audio);
          base64_audio = NULL;

          // Add video file attachment

          char video_header[1024];
          snprintf(video_header, sizeof(video_header), "\r\n--%s\r\n"
                                                       "Content-Type: video/mp4\r\n"
                                                       "Content-Transfer-Encoding: base64\r\n"
                                                       "Content-Disposition: attachment; filename=video.mp4\r\n\r\n",
                   BOUNDARY);

          SSL_write(ssl, video_header, strlen(video_header));

          fp = fopen(videoPath, "rb");
          if (!fp)
          {
            perror("fopen");
            return 1;
          }
          fseek(fp, 0, SEEK_END);
          size = ftell(fp);
          fseek(fp, 0, SEEK_SET);
          char *base64_video = (char *)calloc(size, 1);
          size_t video_len = fread(base64_video, 1, size, fp);
          printf("\nVideo size: %d\n", video_len);
          fclose(fp);

          char *encoded_video = (char *)calloc(video_len * 2, 1);
          size_t video_encoded_len = Base64encode(encoded_video, base64_video, video_len);
          printf("Encoded audio length: %d\n", video_encoded_len);

          SSL_write(ssl, encoded_video, strlen(encoded_video));
          free(encoded_video);
          encoded_video = NULL;
          free(base64_video);
          base64_video = NULL;

          char *end = "\r\n--" BOUNDARY "--\r\n";
          SSL_write(ssl, end, strlen(end));

          char _cmd9[1000];
          strcpy(_cmd9, ".\r\n");
          SSL_write(ssl, _cmd9, strlen(_cmd9));
          sdsd = SSL_read(ssl, recv_buff + recvd, sizeof(recv_buff) - recvd);
          recvd += sdsd;

          char _cmd10[1000];
          strcpy(_cmd10, "QUIT\r\n");
          SSL_write(ssl, _cmd10, strlen(_cmd10));
          sdsd = SSL_read(ssl, recv_buff + recvd, sizeof(recv_buff) - recvd);
          recvd += sdsd;
          printf("0)%s\r\n", &recv_buff);
          free(header);
        }
      }
    }
  }
  return (EXIT_SUCCESS);
}

const char *GetIPAddress(const char *target_domain)
{
  const char *target_ip;
  struct in_addr *host_address;
  struct hostent *raw_list = gethostbyname(target_domain);
  int i = 0;
  for (i; raw_list->h_addr_list[i] != 0; i++)
  {
    host_address = raw_list->h_addr_list[i];
    target_ip = inet_ntoa(*host_address);
  }
  return target_ip;
}

int ConnectToServer(const char *server_address)
{
  int socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(465);
  if (inet_pton(AF_INET, GetIPAddress(server_address), &addr.sin_addr) == 1)
  {
    connect(socket_fd, &addr, sizeof(addr));
  }
  return socket_fd;
}