#include "assembly/wifi.hxx"

#include <cstring>

#include <esp_log.h>
#include <esp_netif.h>
#include <esp_event.h>
#include <esp_wifi.h>

char const static *TAG = "wifi";

namespace wifi
{
    static void print_auth_mode(int authmode)
    {
        switch (authmode)
        {
        case WIFI_AUTH_OPEN:
            ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_OPEN");
            break;
        case WIFI_AUTH_OWE:
            ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_OWE");
            break;
        case WIFI_AUTH_WEP:
            ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WEP");
            break;
        case WIFI_AUTH_WPA_PSK:
            ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA_PSK");
            break;
        case WIFI_AUTH_WPA2_PSK:
            ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA2_PSK");
            break;
        case WIFI_AUTH_WPA_WPA2_PSK:
            ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA_WPA2_PSK");
            break;
        case WIFI_AUTH_ENTERPRISE:
            ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_ENTERPRISE");
            break;
        case WIFI_AUTH_WPA3_PSK:
            ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA3_PSK");
            break;
        case WIFI_AUTH_WPA2_WPA3_PSK:
            ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA2_WPA3_PSK");
            break;
        case WIFI_AUTH_WPA3_ENT_192:
            ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_WPA3_ENT_192");
            break;
        default:
            ESP_LOGI(TAG, "Authmode \tWIFI_AUTH_UNKNOWN");
            break;
        }
    }

    static void print_cipher_type(int pairwise_cipher, int group_cipher)
    {
        switch (pairwise_cipher)
        {
        case WIFI_CIPHER_TYPE_NONE:
            ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_NONE");
            break;
        case WIFI_CIPHER_TYPE_WEP40:
            ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_WEP40");
            break;
        case WIFI_CIPHER_TYPE_WEP104:
            ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_WEP104");
            break;
        case WIFI_CIPHER_TYPE_TKIP:
            ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_TKIP");
            break;
        case WIFI_CIPHER_TYPE_CCMP:
            ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_CCMP");
            break;
        case WIFI_CIPHER_TYPE_TKIP_CCMP:
            ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_TKIP_CCMP");
            break;
        case WIFI_CIPHER_TYPE_AES_CMAC128:
            ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_AES_CMAC128");
            break;
        case WIFI_CIPHER_TYPE_SMS4:
            ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_SMS4");
            break;
        case WIFI_CIPHER_TYPE_GCMP:
            ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_GCMP");
            break;
        case WIFI_CIPHER_TYPE_GCMP256:
            ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_GCMP256");
            break;
        default:
            ESP_LOGI(TAG, "Pairwise Cipher \tWIFI_CIPHER_TYPE_UNKNOWN");
            break;
        }

        switch (group_cipher)
        {
        case WIFI_CIPHER_TYPE_NONE:
            ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_NONE");
            break;
        case WIFI_CIPHER_TYPE_WEP40:
            ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_WEP40");
            break;
        case WIFI_CIPHER_TYPE_WEP104:
            ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_WEP104");
            break;
        case WIFI_CIPHER_TYPE_TKIP:
            ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_TKIP");
            break;
        case WIFI_CIPHER_TYPE_CCMP:
            ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_CCMP");
            break;
        case WIFI_CIPHER_TYPE_TKIP_CCMP:
            ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_TKIP_CCMP");
            break;
        case WIFI_CIPHER_TYPE_SMS4:
            ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_SMS4");
            break;
        case WIFI_CIPHER_TYPE_GCMP:
            ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_GCMP");
            break;
        case WIFI_CIPHER_TYPE_GCMP256:
            ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_GCMP256");
            break;
        default:
            ESP_LOGI(TAG, "Group Cipher \tWIFI_CIPHER_TYPE_UNKNOWN");
            break;
        }
    }

    void init()
    {
        ESP_ERROR_CHECK(esp_netif_init());
        ESP_ERROR_CHECK(esp_event_loop_create_default());
        esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
        assert(sta_netif != nullptr);

        wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
        cfg.nvs_enable = false;
        ESP_ERROR_CHECK(esp_wifi_init(&cfg));

        uint16_t scan_size = 16;
        uint16_t ap_count = 0;
        wifi_ap_record_t ap_info[scan_size];
        memset(ap_info, 0, sizeof(ap_info));

        ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
        ESP_ERROR_CHECK(esp_wifi_start());

        ESP_ERROR_CHECK(esp_wifi_scan_start(nullptr, true));
        ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&scan_size, ap_info));
        ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));

        ESP_LOGI(TAG, "Total APs scanned = %u, actual AP number ap_info holds = %u", ap_count, scan_size);
        for (int i = 0; i < scan_size; i++)
        {
            ESP_LOGI(TAG, "-----------------------------------");
            ESP_LOGI(TAG, "SSID \t\t%s", ap_info[i].ssid);
            ESP_LOGI(TAG, "RSSI \t\t%d", ap_info[i].rssi);
            print_auth_mode(ap_info[i].authmode);
            if (ap_info[i].authmode != WIFI_AUTH_WEP)
            {
                print_cipher_type(ap_info[i].pairwise_cipher, ap_info[i].group_cipher);
            }
            ESP_LOGI(TAG, "Channel \t\t%d", ap_info[i].primary);
        }
    }
}
