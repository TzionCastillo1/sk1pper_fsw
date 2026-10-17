#include "param_mgr.h"
#include "string.h"
#include "stdlib.h"
#include "fatfs.h"
#include "sensor_mgr.h"

#include "printf/printf.h"

#define FATFS_LINE_BUFF_LEN     64
#define PARAM_DELIM             ","
#define PARAM_MIN_ASCII         32
#define PARAM_MAX_ASCII         126

#define PARAM_GYRO_KEY "gyro"

//Default param values
#define DEFAULT_PID             0.0
#define MIN_PID                 0.0
#define MAX_PID                 10


typedef struct param_t
{
    char *key;
    float val;
    float min;
    float max;
} param_t;

param_t param_table[] = 
{
    {"roll_pid_kp", DEFAULT_PID, MIN_PID, MAX_PID},
    {"roll_pid_ki", DEFAULT_PID, MIN_PID, MAX_PID},
    {"", 0,0,0},
};

FATFS FatFs;
FIL fil;

error_t param_mgr_init(void)
{
    FRESULT fres;

    fres = f_mount(&FatFs, "", 1);
    if (fres != FR_OK)
    {
        printf_("f_mount error (%i)\r\n", fres);
    }

    DWORD free_clusters, free_sectors, total_sectors;

    FATFS* getFreeFs;

    fres = f_getfree("", &free_clusters, &getFreeFs);
    if (fres != FR_OK) {
        printf_("f_getfree error (%i)\r\n", fres);
    }

    else
    {
        //Formula comes from ChaN's documentation
        total_sectors = (getFreeFs->n_fatent - 2) * getFreeFs->csize;
        free_sectors = free_clusters * getFreeFs->csize;

        printf_("SD card stats:\r\n%10lu KiB total drive space.\r\n%10lu KiB available.\r\n", total_sectors / 2, free_sectors / 2);
    }



}

error_t param_mgr_get(char *key, float *value)
{
    int param_idx;
    error_t err = param_mgr_find(key, &param_idx);
    if (err == ERROR_OK)
    {
        *value = param_table[param_idx].val;
    }

    return err;

}

error_t param_mgr_get_gnc(gnc_params_t *gnc_params)
{

}

error_t param_mgr_set(char *key, float value)
{
    int param_idx;
    error_t err = param_mgr_find(key, &param_idx);
    if (err == ERROR_OK)
    {
        if ( (value >= param_table[param_idx].min) && (value <= param_table[param_idx].max) )
        {
            printf_("setting %s %f\r\n", key, value);
            param_table[param_idx].val = value;
        }
        else
        {
            err = ERROR_PARAM_INVALID_VALUE;
        }
    }

    return err;

}

error_t param_mgr_save(void)
{
    FRESULT fres;
    error_t res = ERROR_OK;
    char writeBuff[128];
    
    fres = f_open(&fil, "params.csv", FA_WRITE | FA_OPEN_APPEND | FA_CREATE_ALWAYS);
    if (fres == FR_OK)
    {
        printf_("Opened params.csv for writing\r\n");
        for (int param_idx = 0; param_table[param_idx].key != NULL; param_idx++)
        {
            snprintf_(writeBuff, sizeof(writeBuff), "%s,%f\r\n", param_table[param_idx].key, param_table[param_idx].val);
            //Could not get the f_printf() function to work, so this is a crude workaround
            for (int idx = 0; writeBuff[idx] != NULL; idx++)
            {
                fres = f_putc(writeBuff[idx], &fil);
            }
            //fres = f_write(&fil, writeBuff, )
           //f_printf(&fil, "%s,%f\r\n", param_table[param_idx].key, param_table[param_idx].val); 
        }
        printf_("Parameters written\r\n");
    }
    else
    {
        printf_("Unable to open params.csv for writing\r\n");
        res = ERROR_PARAM_WRITE_FAIL;
    }

    f_close(&fil);

    return res;

}

error_t param_mgr_load(void)
{
    FRESULT fres;

    //Now let's try to open file "params.csv"
    fres = f_open(&fil, "params.csv", FA_READ);
    if (fres != FR_OK) {
        printf_("f_open error (%i)\r\n");
    }
    else
    {
        printf_("params.csv succesfully opened\r\n");
    }

    //Read a string (line) up to 64 bytes from "test.txt" on the SD card
    BYTE readBuf[FATFS_LINE_BUFF_LEN];

    //We can either use f_read OR f_gets to get data out of files
    //f_gets is a wrapper on f_read that does some string formatting for us
    TCHAR* rres = f_gets((TCHAR*)readBuf, FATFS_LINE_BUFF_LEN, &fil);
    while(rres != 0) {
        char *saveptr;
        char *key = strtok_r(readBuf, PARAM_DELIM, &saveptr);
        char *val_str = strtok_r(NULL, PARAM_DELIM, &saveptr);

        float val = strtof(val_str, NULL);

        param_mgr_set(key, val);
        rres = f_gets((TCHAR*)readBuf, FATFS_LINE_BUFF_LEN, &fil);
    }
    printf_("f_gets error (%i)\r\n", fres);
    

    //Be a tidy kiwi - don't forget to close your file!
    f_close(&fil);

    //We're done, so de-mount the drive
    //f_mount(NULL, "", 0);
}

error_t param_mgr_find(char *key, uint32_t *idx)
{
    error_t ret = ERROR_PARAM_NOT_FOUND;

    //Iterate through param table looking for a matching key
    for (uint32_t param_idx = 0; param_table[param_idx].key != NULL; param_idx++)
    {
        if (strcmp(param_table[param_idx].key, key) == 0)
        {
            *idx = param_idx;
            ret = ERROR_OK;
        }
    }
    return ret;
}

error_t param_mgr_get_from_idx(uint32_t idx, char *key, float *value)
{
    if (idx >= param_mgr_get_count()) return ERROR_PARAM_INDEX_OUT_OF_BOUNDS;
    strncpy(key, param_table[idx].key, PARAM_KEY_MAX_LENGTH);
    *value = param_table[idx].val;
    return ERROR_OK;
}

int param_mgr_get_count()
{
    //Should work because the 'key' in the param table is a pointer
    //to a string literal and therefore should all be the same size
    //Subtract one to remove the end of table entry
    return (sizeof(param_table) / sizeof(param_table[0])) - 1;
} 