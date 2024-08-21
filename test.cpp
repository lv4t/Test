#include <winsock2.h>
#include <stdio.h>

int main() {
  // Khởi tạo Winsock2
  WSADATA wsaData;
  int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (iResult != 0) {
    printf("Khởi tạo Winsock2 thất bại: %d\n", iResult);
    return 1;
  }

  // Tạo socket
  SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sock == INVALID_SOCKET) {
    printf("Tạo socket thất bại: %d\n", WSAGetLastError());
    WSACleanup();
    return 1;
  }

  // Kết nối với máy chủ SMTP
  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.
serverAddr.sin_addr.s_addr = inet_addr("smtp.example.com"); // Thay thế "smtp.example.com" bằng địa chỉ máy chủ SMTP thực tế
serverAddr.sin_port = htons(25); // Cổng SMTP mặc định là 25
int iResult = connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
if (iResult == SOCKET_ERROR) {
  printf("Kết nối với máy chủ SMTP thất bại: %d\n", WSAGetLastError());
  closesocket(sock);
  WSACleanup();
  return 1;
}
char recvBuf[1024];
int recvLen = recv(sock, recvBuf, sizeof(recvBuf), 0);
if (recvLen == SOCKET_ERROR) {
  printf("Lỗi khi nhận dữ liệu từ máy chủ: %d\n", WSAGetLastError());
  closesocket(sock);
  WSACleanup();
  return 1;
}

printf("%s\n", recvBuf); // In ra thông báo từ máy chủ

// Gửi lệnh EHLO
send(sock, "EHLO\r\n", 6, 0);

recvLen = recv(sock, recvBuf, sizeof(recvBuf), 0);
if (recvLen == SOCKET_ERROR) {
  printf("Lỗi khi nhận dữ liệu từ máy chủ: %d\n", WSAGetLastError());
  closesocket(sock);
  WSACleanup();
  return 1;
}

printf("%s\n", recvBuf); // In ra thông báo từ máy chủ
// Tạo nội dung email
std::string emailContent = "Nội dung email của bạn...";

// Tạo chuỗi email hoàn chỉnh
std::string emailStr = "Subject: Tiêu đề email\r\n\r\n" + emailContent + "\r\n";

// Xác định kích thước email
size_t emailSize = emailStr.size();
// Gửi lệnh MAIL FROM
send(sock, "MAIL FROM: <your_email@example.com>\r\n", 34, 0);

recvLen = recv(sock, recvBuf, sizeof(recvBuf), 0);
if (recvLen == SOCKET_ERROR) {
  printf("Lỗi khi nhận dữ liệu từ máy chủ: %d\n", WSAGetLastError());
  closesocket(sock);
  WSACleanup();
  return 1;
}

printf("%s\n", recvBuf); // In ra thông báo từ máy chủ

// Gửi lệnh DATA
send(sock, "DATA\r\n", 5, 0);

recvLen = recv(sock, recvBuf, sizeof(recvBuf), 0);
if (recvLen == SOCKET_ERROR) {
  printf("Lỗi khi nhận dữ liệu từ máy chủ: %d\n", WSAGetLastError());
  closesocket(sock);
  WSACleanup();
  return 1;
}

printf("%s\n", recvBuf); // In ra thông báo từ máy chủ

// Gửi nội dung email
send(sock, emailStr.c_str(), emailSize, 0);

recvLen = recv(sock, recvBuf, sizeof(recvBuf), 0);
if (recvLen == SOCKET_ERROR) {
  printf("Lỗi khi nhận dữ liệu từ máy chủ: %d\n", WSAGetLastError());
  closesocket(sock);
  WSACleanup();
  return 1;
}

printf("%s\n", recvBuf); // In ra thông báo từ máy chủ
// Gửi lệnh QUIT
send(sock, "QUIT\r\n", 5, 0);

closesocket(sock);
WSACleanup();

printf("Gửi email thành công!\n");
}