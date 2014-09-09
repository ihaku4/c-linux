#include <stdio.h>
#include <string.h>

struct kv_pair {
  char *key, value;
};

struct config_unit {
  char *comment, name;
  struct kv_pair content[];
};

int is_blank(char c)
{
  return c == ' ' || c == '\t';
}

char *trim(char *line)
{
  int i, j, len;
  for (i = 0; is_blank(*line); line++);
  len = strlen(line);
  for (j = len-1; is_blank(line[j]); j--) {
    line[j] = '\0';
  }
  return line;
}

int main(void)
{

  char *test_ini_content = ";Configuration of http\n\
[http]\n\
domain=www.mysite.com\n\
port=8080\n\
cgihome=/cgi-bin\n\
 \n\
;Configuration of db\n\
[database]\n\
server = mysql\n\
user = myname\n\
password = toopendatabase"; // BUG: blank characters need at blank line.

  char ini_str[1000];
  char xml[1000];
  char *XML_COMMENT_START = "<!-- ";
  char *XML_COMMENT_END = " -->";
  
  int i, j, len;
  char *line;
  struct config_unit u;
  char *current_name = NULL;
  char *current_key = NULL;
  char *current_value = NULL;
  char *key_saveptr;
  len = strlen(test_ini_content);
  memcpy(ini_str, test_ini_content, len);
  ini_str[len] = '\n';
  ini_str[len+1] = ' ';
  ini_str[len+2] = '\0';
  line = strtok(ini_str, "\n");
  for (i = 0; line != NULL; line = strtok(NULL, "\n")) {
    line = trim(line);
    if (strlen(line) == 0 && current_name != NULL) {
        xml[i++] = '<';
        xml[i++] = '/';
        len = strlen(current_name);
        memcpy(xml+i, current_name, len);
        i += len;
        xml[i++] = '>';
        xml[i++] = '\n';
        xml[i++] = '\n';
        continue;
    }
    switch (line[0]) {
      case ';':
        len = strlen(XML_COMMENT_START);
        memcpy(xml+i, XML_COMMENT_START, len);
        i += len;
        len = strlen(line+1);
        memcpy(xml+i, line+1, len);
        i += len;
        len = strlen(XML_COMMENT_END);
        memcpy(xml+i, XML_COMMENT_END, len);
        i += len;
        xml[i++] = '\n';
        break;
      case '[':
        current_name = line+1;
        for (j = 0; line[j] != ']' && line[j] != '\0'; j++);
        line[j] = '\0';
        xml[i++] = '<';
        len = strlen(current_name);
        memcpy(xml+i, current_name, len);
        i += len;
        xml[i++] = '>';
        xml[i++] = '\n';
        break;
      default:
        current_key = strtok_r(line, "=", &key_saveptr);
        current_key = trim(current_key);
        xml[i++] = '\t';
        xml[i++] = '<';
        len = strlen(current_key);
        memcpy(xml+i, current_key, len);
        i += len;
        xml[i++] = '>';
        current_value = strtok_r(NULL, "=", &key_saveptr);
        if (current_value != NULL) {
          current_value = trim(current_value);
          len = strlen(current_value);
          memcpy(xml+i, current_value, len);
          i += len;
        }
        xml[i++] = '<';
        xml[i++] = '/';
        len = strlen(current_key);
        memcpy(xml+i, current_key, len);
        i += len;
        xml[i++] = '>';
        xml[i++] = '\n';
        break;
    }
  }
  xml[i++] = '\0';
  //printf("%s", test_ini_content);
  printf("%s", xml);
  return 0;

}

struct config_unit parse_ini_string(const char* ini)
{
  struct config_unit u;
  return u;
}


