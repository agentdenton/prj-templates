#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>

#define PR_DEBUG(fmt, ...) fprintf(stdout, "DEBUG: " fmt "\n", ##__VA_ARGS__)
#define PR_INFO(fmt, ...) fprintf(stdout, "INFO: " fmt "\n", ##__VA_ARGS__)
#define PR_WARN(fmt, ...) fprintf(stdout, "WARN: " fmt "\n", ##__VA_ARGS__)
#define PR_ERR(fmt, ...) fprintf(stderr, "ERROR: " fmt "\n", ##__VA_ARGS__)

#define PR_ERR_EXIT(fmt, ...) do { \
  PR_ERR(fmt, ##__VA_ARGS__); \
  exit(1); \
} while (0)

#define ARRAY_LEN(x) (sizeof(x) / sizeof(x[0]))

typedef struct if_settings {
  char *ifname;
  char *addr;
  char *vlan_id;
} if_settings_t;

static int run_cmd(const char *cmd[], uint8_t *output, size_t output_size) {
  assert(cmd != NULL);

  char cmd_as_str[1024];
  cmd_as_str[0] = '\0';
  for (int i = 0; cmd[i] != NULL; ++i) {
    strcat(cmd_as_str, cmd[i]);
    if (cmd[i + 1] != NULL) {
      strcat(cmd_as_str, " ");
    }
  }

  PR_INFO("Running %s command", cmd_as_str);

  FILE *f = popen(cmd_as_str, "r");
  if (f == NULL) {
    PR_ERR("Failed to popen on %s", cmd_as_str);
    return -1;
  }

  ssize_t bytes = fread(output, 1, output_size - 1, f);
  if (bytes < 0) {
    PR_ERR("Error reading output from %s process", cmd_as_str);
    return -1;
  }
  output[bytes] = '\0';

  int status = pclose(f);
  if (WIFEXITED(status)) {
    int exit_status = WEXITSTATUS(status);
    if (exit_status != 0) {
      PR_ERR("Subprocess failed with exit status %d", exit_status);
      return -1;
    }
  } else {
    PR_ERR("Subprocess terminated abnormally");
    return -1;
  }
  return 0;
}

int if_set_up(const char *ifname) {
  PR_INFO("%s: %s", __func__, ifname);
  uint8_t buf[1024];
  const char *cmd[] = {"ip", "link", "set", ifname, "up", NULL};
  if (run_cmd(cmd, buf, ARRAY_LEN(buf)) < 0) {
    PR_ERR("Failed to set %s up", ifname);
    return -1;
  }
  return 0;
}

int if_set_down(const char *ifname) {
  PR_INFO("%s: %s", __func__, ifname);
  uint8_t buf[1024];
  const char *cmd[] = {"ip", "link", "set", ifname, "down", NULL};
  if (run_cmd(cmd, buf, ARRAY_LEN(buf)) < 0) {
    PR_ERR("Failed to set %s down", ifname);
    return -1;
  }
  return 0;
}

bool is_if_up(const char *ifname) {
  uint8_t buf[1024];
  const char *cmd[] = {"ip", "link", "show", "dev", ifname, NULL};
  if (run_cmd(cmd, buf, ARRAY_LEN(buf)) < 0) {
    PR_ERR("Failed to run 'ip link show dev %s' command", ifname);
    return false;
  }
  if (strstr((const char *)buf, "DOWN") != NULL) {
    return false;
  } else {
    return true;
  }
}

int if_add_addr(if_settings_t s, const char *ifname, const char *addr) {
  PR_INFO("%s: %s %s", __func__, ifname, addr);
  uint8_t buf[1024];
  const char *cmd[] = {"ip", "addr", "add", addr, "dev", ifname, NULL};
  if (run_cmd(cmd, buf, ARRAY_LEN(buf)) < 0) {
    PR_ERR("Failed to add addr %s to %s down", addr, ifname);
    return -1;
  }
  return 0;
}

int if_rm_addr(const char *ifname, const char *addr) {
  PR_INFO("%s: %s %s", __func__, ifname, addr);
  uint8_t buf[1024];
  const char *cmd[] = {"ip", "addr", "del", addr, "dev", ifname, NULL};
  if (run_cmd(cmd, buf, ARRAY_LEN(buf)) < 0) {
    PR_ERR("Failed to delete addr %s for %s down", addr, ifname);
    return -1;
  }
  return 0;
}

int add_if_vlan(if_settings_t s, const char *ifname, uint32_t id) {
  PR_INFO("%s: %s, vlan id: %d", __func__, ifname, id);

  char id_str[256];
  snprintf(id_str, ARRAY_LEN(id_str), "%d", id);

  char if_and_vlan_id[512];
  snprintf(if_and_vlan_id, ARRAY_LEN(if_and_vlan_id), "%s.%s", ifname, id_str);

  uint8_t buf[1024];
  const char *cmd[] = {
    "ip", "link", "add", "link", ifname, "name", if_and_vlan_id, "type", "vlan", "id", id_str, NULL
  };
  if (run_cmd(cmd, buf, ARRAY_LEN(buf)) < 0) {
    PR_ERR("Failed to add vlan device %s with id %d", ifname, id);
    return -1;
  }
  return 0;
}

int rm_if_vlan(if_settings_t s, const char *ifname, uint32_t id) {
  PR_INFO("%s: %s, vlan id: %d", __func__, ifname, id);

  char id_str[256];
  snprintf(id_str, ARRAY_LEN(id_str), "%d", id);

  char if_and_vlan_id[512];
  snprintf(if_and_vlan_id, ARRAY_LEN(if_and_vlan_id), "%s.%s", ifname, id_str);

  uint8_t buf[1024];
  const char *cmd[] = {"ip", "link", "del", "link", ifname, "name", if_and_vlan_id, NULL};
  if (run_cmd(cmd, buf, ARRAY_LEN(buf)) < 0) {
    PR_ERR("Failed to delete vlan device %s with id %d", ifname, id);
    return -1;
  }
  return 0;
}

int network_cfg_from_settings(const if_settings_t s) {
  return 
}

int main() {
  if_settings_t *eth0 = (if_settings_t *)malloc(sizeof(if_settings_t))
  return 0;
}
