
#include "xls/xls.h"
#include <stdlib.h>
#include <string.h>
// #include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "lang_xls.h"
#include "language_new.h"
// #include "user_data.h"

#define LAN_ERR(format, ...) printf("\e[0;1;31m"                             \
                                    "[LANGUAGE ][%s:%04u]\t" format "\e[0m", \
                                    __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LAN_INFO(format, ...) printf("\e[0;1m"                                \
                                     "[LANGUAGE ][%s:%04u]\t" format "\e[0m", \
                                     __FUNCTION__, __LINE__, ##__VA_ARGS__)

typedef struct
{
    bool xls_is_exist;    // xls文件存在标志位
    int xls_null_str_num; // xls文件 在有效行列中 存在空字符的数量
    int row_total;        // xls文档的有效总行数
    int col_total;        // xls文档的有效总列数
} xls_info_t;

xls_info_t xls_info = {false, 0, 0, 0};

char ***buffer = NULL;
// /*******************************************************************
//  * @brief  字符串替换
//  * @return {char}
//  * @param  {char} source 初始字符串
//  * @param  {char} find 需要被替换的子串
//  * @param  {char} replace 替换成的字符串
//  *******************************************************************/
void str_replace(char *source, const char *find, const char *replace)
{
    char *new_string;
    char *ptr;
    char *tmp;
    int find_len = strlen(find);
    int replace_len = strlen(replace);
    int buffer_size = 2 * strlen(source);

    new_string = (char *)malloc(buffer_size);

    ptr = source;
    tmp = new_string;

    while (*ptr != '\0')
    {
        if (strncmp(ptr, find, find_len) == 0)
        {
            strncpy(tmp, replace, replace_len);
            ptr += find_len;
            tmp += replace_len;
        }
        else
        {
            *tmp++ = *ptr++;
        }
    }

    *tmp = '\0';

    strcpy(source, new_string);
    free(new_string);
}

// /*******************************************************************
//  * @brief  初始化xls文件，加载语言字符串至内存
//  * @return {char ***} NULL：初始化失败  buffer地址：初始化成功，返回动态申请的三维字符数组
//  * @param  {int} sheet_num excel表格中的工作表序号，从零开始
//  *******************************************************************/
char ***lang_xls_init(int sheet_num)
{
    xlsWorkBook *pWb = NULL;
    xlsWorkSheet *pWs = NULL;

    if (access(XLS_TMP_PATH, F_OK) != 0)
    {
        // LOG_RED(XLS_TMP_PATH " not exists!\n");
        printf(XLS_TMP_PATH " not exists!!!!!!!!!!!!!!\n");
        // printf("%d!!!!!!!!!!!!!!\n", access(XLS_TMP_PATH, F_OK));

        return NULL;
    }
    pWb = xls_open(XLS_TMP_PATH, CODE);
    if (NULL == pWb)
    {
        LAN_ERR(XLS_TMP_PATH " open failed\n");
        return NULL;
    }
    pWs = xls_getWorkSheet(pWb, sheet_num); // pWs指向第 sheet_num 个 Sheet
    xls_parseWorkSheet(pWs);
#if (0)
    /* 根据程序固定读取 */
    xls_info.row_total = LANGUAGE_STRING_TOTAL;
    xls_info.col_total = LANGUAGE_TOTAL;
#else
    /* 根据表格文件读取 */
    xls_info.row_total = pWs->rows.lastrow + 1;
    xls_info.col_total = pWs->rows.lastcol;
#endif

    buffer = (char ***)malloc(sizeof(char ***) * xls_info.row_total);
    if (buffer == NULL)
        return NULL;

    for (int i = 0; i < xls_info.row_total; i++)
    {
        buffer[i] = (char **)malloc(sizeof(char **) * xls_info.col_total);
        if (buffer[i] == NULL)
            return NULL;

        for (int j = 0; j < xls_info.col_total; j++)
        {
            if ((&(pWs->rows.row[i]))->cells.cell[j].str == NULL)
            {
                buffer[i][j] = (char *)malloc(5);
                if (buffer[i][j] == NULL)
                    return NULL;

                sprintf(buffer[i][j], "NULL");
                xls_info.xls_null_str_num++;
            }
            else
            {
                buffer[i][j] = (char *)malloc(strlen((char *)(&(pWs->rows.row[i]))->cells.cell[j].str) + 1);
                if (buffer[i][j] == NULL)
                    return NULL;

                strcpy(buffer[i][j], (char *)((&(pWs->rows.row[i]))->cells.cell[j].str));
                str_replace(buffer[i][j], "\\n", "\n");
            }
            printf("%s\t", (char *)((&(pWs->rows.row[i]))->cells.cell[j].str));
        }
        printf("\n");
    }
    xls_close_WS(pWs);
    xls_close_WB(pWb);
    xls_info.xls_is_exist = true;

    return buffer;
}

/*******************************************************************
 * @brief  获取xls文件状态，查看文件 是否存在 并 初始化成功
 * @return {bool} false：文件不存在  true：文件存在
 *******************************************************************/
bool lang_xls_file_state_get(void)
{
    return xls_info.xls_is_exist;
}

/*******************************************************************
 * @brief  获取xls文件中 在有效行列中 含有的空字符数量
 * @return {int}
 *******************************************************************/
int lang_xls_null_str_num_get(void)
{
    return xls_info.xls_null_str_num;
}

/*******************************************************************
 * @brief  获取xls文件中语言的数量（即列数）
 * @return {int}
 *******************************************************************/
int lang_xls_language_num_get(void)
{
    return xls_info.col_total;
}

/*******************************************************************
 * @brief  获取xls文件中单个字符串的数量（即行数）
 * @return {int}
 *******************************************************************/
int lang_xls_str_num_get(void)
{
    return xls_info.row_total;
}

/*******************************************************************
 * @brief  获取xls文件中指定单元格的字符串
 * @return {char *}
 * @param  {int} str_num 字符串的序号（行号） 从0起
 * @param  {int} lang_type 字符串的语言类型（列号） 从0起
 *******************************************************************/
char *lang_xls_str_get(int str_num, int lang_type)
{
    // if (buffer[str_num][lang_type] == NULL)
    //     return "NULL";
    // printf("%d!!!!!!!!!!!!!!!!!行\n", str_num);
    // printf("%d!!!!!!!!!!!!!!!!!列\n", lang_type);
    // printf("====buffer[2][1] is %s\n", buffer[2][1]);
    return buffer[str_num][lang_type];
}

static bool is_lan_xls_init_ok = false;

bool is_lan_xls_init_ok_get()
{
    return is_lan_xls_init_ok;
}

/* 初始化 */
bool init_language_xls_info(void)
{
    if (lang_xls_init(0) == NULL)
    {
        // LOG_RED("lan init err..\n");
        printf("lan init err..\n\n");
        return false;
    }
    // printf("11111111111111111111111111111111111\n\n");

    if (lang_xls_file_state_get() == false)
    {
        printf("No language file,use default language\n ");
        // LOG_RED("No language file,use default language\n ");
        return false;
    }

    // printf("22222222222222222222222222222222222\n\n");

    if (lang_xls_null_str_num_get() > 0)
    {
        printf("lan get NULL %d \n", lang_xls_null_str_num_get());
        // LOG_YELLOW("lan get NULL %d \n", lang_xls_null_str_num_get());
    }
    // printf("33333333333333333333333333333333333\n\n");

    if (lang_xls_str_num_get() != LANGUAGE_STRING_TOTAL + 1)
    {
        printf("XLS表总列数%d\n", lang_xls_str_num_get());
        printf("id总列数%d\n", LANGUAGE_STRING_TOTAL);
        // LOG_RED("xls lan get str[%d] != LANGUAGE_STRING_TOTAL[%d] \n", lang_xls_str_num_get(), LANGUAGE_STRING_TOTAL);
        return false;
    }

    // printf("44444444444444444444444444444444444\n\n");
    if (lang_xls_language_num_get() == 0)
    {
        printf("The number of language is zero,use default language==============\n ");
        // LOG_RED("The number of language is zero,use default language\n ");
        return false;
    }

    is_lan_xls_init_ok = true;
    return true;
}
