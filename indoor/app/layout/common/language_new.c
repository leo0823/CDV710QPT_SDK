#include "language_new.h"
#include "user_data.h"
#include "string.h"
#include "lang_xls.h"
#include "stdio.h"
static char *layout_default_language_string[LANGUAGE_STRING_TOTAL] =
    {

        "Settings",

        "General",

        "WIFI",

        "Sound",

        "Screen",

        "Recording/Monitoring",

        "Installation configuration",

        "Auto setup",

        "Date and time",

        "language",

        "Password",

        "Change password for security",

        "Storage space",

        "Door opening method",

        "Open the door after calling",

        "Open the door when called",

        "Door opener module",

        "Door camera",

        "Digital door lock",

        "Door camera #2 : Number of door openings",

        "2Door",

        "call time",

        "1 minute",

        "3 minute",

        "5 minute",


        "Download mobile app",

        "Initialization user data",

        "Version information",


};

char *lang_str_get(lang_str_id_t lang_str_id)
{
    if (lang_xls_file_state_get()   == true && 
        lang_xls_language_num_get() > 0 &&
        lang_xls_str_num_get() == LANGUAGE_STRING_TOTAL)
    {
        if(strcmp("NULL", lang_xls_str_get(lang_str_id, user_data_get()->etc.language)) == 0)
        {
            printf("=======%d=======%s==\n",__LINE__,__func__);
            return lang_xls_str_get(lang_str_id, LANGUAGE_ENGLISH);
        }
        printf("=======%d=======%s==\n",__LINE__,__func__);
        return lang_xls_str_get(lang_str_id, user_data_get()->etc.language);

    }
    else
    {
         printf("=======%d=======%s==\n",__LINE__,__func__);
        return layout_default_language_string[lang_str_id];
    }
}

char *lang_str_get_by_language(lang_str_id_t index, layout_language_t language)
{
    if (lang_xls_file_state_get()   == true && 
        lang_xls_language_num_get() > 0 &&
        lang_xls_str_num_get() == LANGUAGE_STRING_TOTAL)
    {
        if(strcmp("NULL", lang_xls_str_get(index, language)) == 0)
        {
            return lang_xls_str_get(index, LANGUAGE_ENGLISH);
        }
        
        return lang_xls_str_get(index, language);

    }
    else
    {
        return layout_default_language_string[index];
    }
}

int language_total_get(void)
{
    if (lang_xls_file_state_get()   == true && 
        lang_xls_language_num_get() > 0  &&
        /* lang_xls_null_str_num_get() == 0 && */ 
        lang_xls_str_num_get() == LANGUAGE_STRING_TOTAL)
    {
        return lang_xls_language_num_get();
    }

    return 1;
}


/*************************************************************************
 * @brief  输出全部语言文本到指定文件, 主要用于检查文案是否出错
 * @date   2022-12-02 09:06
 * @author xiaoele
 **************************************************************************/
void write_language_string_to_xls(void)
{
#if (0)
	#define LANGUAGE_STRING_XLS "/tmp/nfs/language_default.csv"    

	int fd = open(LANGUAGE_STRING_XLS, O_RDWR);
	if(fd < 0)
	{
		LAN_ERR("%s open fail..\n", LANGUAGE_STRING_XLS);
		return;
	}

	/* string */
	for(int i = 0; i < LANGUAGE_STRING_TOTAL; i++)
	{
        char buf[128] = {0};
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "%s\n", lang_str_get(i));        
        write(fd, buf, strlen(buf));

	}

	close(fd);


#endif 
}


// /* 时间显示格式
// 长日期	
// 中文	2023年2月24日 星期五
// 英文	Fri. 24/02/2023

//  */


// char *data_fmt_string_get(struct tm *time)
// {
// 	static char buf[32] = {0};
// 	memset(buf, 0, sizeof(buf));
// 	int   year = time->tm_year + 1900;
// 	int   mmon = time->tm_mon + 1;
// 	int   mday = time->tm_mday;
// 	char *week = lang_str_get(time->tm_wday + WEEK_SUN);

// 	switch (user_data_get()->etc.language)
// 	{
// 	case LANGUAGE_ENGLISH:
// 		sprintf(buf, "%s %02d/%02d/%04d", week, mmon, mday, year);
// 		break;

// 	case LANGUAGE_CHINESE:
// 		sprintf(buf, "%04d/%02d/%02d %s", year, mday, mmon, week);
	
// 	default:
// 		break;
// 	}

// 	// LOG_YELLOW("date fmt:%s\n", buf);



// 	return buf;
// }

