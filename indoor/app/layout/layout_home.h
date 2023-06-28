#ifndef _LAYOUT_HOME_H_
#define _LAYOUT_HOME_H_
#include "common/language.h"

typedef enum
{
        HOME_LANG_ID_USE_MOBILE_APP,
        HOME_LANG_ID_RECENT_VIDEO, // 启动设置
        HOME_LANG_ID_RECENT_CALL,
        HOME_LANG_ID_MONITORING,
        HOME_LANG_ID_CALL,
        HOME_LANG_ID_CCTV,
        HOME_LANG_ID_AWAY,
        HOME_LANG_ID_BURGLAR,
        HOME_LANG_ID_ELEVATOR,
        HOME_LANG_ID_EMERGENCY,
        HOME_LANG_ID_THE_COMMUNICATION_LINE,
        HOME_LANG_ID_DOORCAMERA,
        HOME_LANG_ID_COMMON_ENTRANCE,
        HOME_LANG_ID_TOTAL

} LAYOUT_HOME_LANG_ID;

static const char *layout_home_language[HOME_LANG_ID_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {"Currently in use in mobile app.", "Currently in use in mobile app.", "Currently in use in mobile app."},
        {"Recent Video", "Recent Video", "Recent Video"},
        {"Recent call", "Recent call", "Recent call"},
        {"Monitoring", "监控","Наблюдение","Monitoring","Monitoreo","Quan sát","مراقبة "},
        {"Call", "呼入", "Call","Вызов","Llamar","Gọi","إتصال"},
        {"CCTV", "CCTV", "CCTV","Видеонаблюдение","CCTV","CCTV","CCTV"},
        {"외출", "外出", "Away","Отсутствие","Salida","Vắng nhà","بعيد"},
        {"Burglar", "Burglar", "Burglar"},
        {"Elevator","Elevator","Elevator",},
        {"Emergency", "Emergency", "Emergency"},
        {"The communication line is being used\nby another device.", "The communication line is being used\nby another device.", "The communication line is being used\nby another device."},
        {"Door Camera", "Door Camera", "Door Camera"},
        {"Common entrance", "Common entrance", "Common entrance"},
    };

/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：年/년 !@
***/
static inline const char *layout_home_language_get(LAYOUT_HOME_LANG_ID id)
{
        return layout_home_language[id][language_id_get()];
}

static const char *layout_home_week_language[7][LANGUAGE_ID_TOTAL] = {

    /* HOME_LANG_ID_WEEK_1 */
    {"월요일", "星期一", "Mon", "Понедельник", "Lunes", "Pazartesi", "Poniedziałek", "Pondělí", "الإثنين"},
    /* HOME_LANG_ID_WEEK_2 */
    {"화요일", "星期二", "Tue", "Вторник", "Martes", "Salı", "Wtorek", "Úterý", "الثلاثاء"},
    /* HOME_LANG_ID_WEEK_3 */
    {"수요일", "星期三", "Wed", "Среда", "Miércoles", "Çarşamba", "Środa", "Středa", "الاربعاء"},
    /* HOME_LANG_ID_WEEK_4 */
    {"목요일", "星期四", "Thu", "Четверг", "Jueves", "Perşembe", "Czwartek", "Čtvrtek", "الخميس"},
    /* HOME_LANG_ID_WEEK_5 */
    {"금요일", "星期五", "Fri", "Пятница", "Viernes", "Cuma", "Piątek", "Pátek", "الجمعة"},
    /* HOME_LANG_ID_WEEK_6 */
    {"토요일", "星期六", "Sat", "Суббота", "Sábado", "Cumartesi", "Sobota", "Sobota", "السبت"},
    /* HOME_LANG_ID_WEEK_7 */
    {"일요일", "星期日", "Sun", "Воскресенье", "Domingo", "Pazar", "Niedziela", "Pátek", "الأحد"},

};
/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：星期文本
***/
static inline const char *layout_home_week_language_get(int week)
{
        return layout_home_week_language[week][language_id_get()];
}

static const char *layout_home_month_language[32][LANGUAGE_ID_TOTAL] = {
    /*HOME_LANG_ID_MONTH_1 */
    {"1월", "1月", "January", "Январь", "Ene", "Ocak", "Styczeń", "Leden", "يناير"},
    /*HOME_LANG_ID_MONTH_2 */
    {"2월", "2月", "February", "Февраль", "Feb", "Şubat", "Luty", "Únor", "فبراير"},
    /*HOME_LANG_ID_MONTH_3 */
    {"3월", "3月", "March", "Март", "Mar", "Mart", "Marzec", "Březen", "مارس"},
    /*HOME_LANG_ID_MONTH_4 */
    {"4월", "4月", "April", "Апрель", "Abr", "Nisan", "Kwiecień", "Duben", "أبريل"},
    /*HOME_LANG_ID_MONTH_5 */
    {"5월", "5月", "May", "Май", "May", "Mayıs", "Maj", "Květen", "مايو"},
    /*HOME_LANG_ID_MONTH_6 */
    {"6월", "6月", "June", "Июнь", "Jun", "Haziran", "Czerwiec", "Červen", "يونيو"},
    /*HOME_LANG_ID_MONTH_7 */
    {"7월", "7月", "July", "Июль", "Jul", "Temmuz", "Lipiec", "Červenec", "يوليو"},
    /*HOME_LANG_ID_MONTH_8 */
    {"8월", "8月", "August", "Август", "Ago", "Ağustos ayında", "Sierpień", "Srpen", "أغسطس"},
    /*HOME_LANG_ID_MONTH_9 */
    {"9월", "9月", "September", "Сентябрь", "Sep", "Eylül", "Wrzesień", "Září", "سبتمبر"},
    /*HOME_LANG_ID_MONTH_10 */
    {"10월", "10月", "October", "Октябрь", "Oct", "Ekim", "Październik", "Říjen", "اكتوبر"},
    /*HOME_LANG_ID_MONTH_11 */
    {"11월", "11月", "November", "Ноябрь", "Nov", "Kasım", "Listopad", "Listopad", "نوفمبر"},
    /*HOME_LANG_ID_MONTH_12 */
    {"12월", "12月", "December", "Декабрь", "Dic", "Aralık", "Grudzień", "Prosinec", "ديسمبر"},
};
/***
** 日期: 2022-04-26 09:16
** 作者: leo.liu
** 函数作用：获取home页面的字符串资源
** 返回参数说明：月份文本
***/
static inline const char *layout_home_month_language_get(int mon)
{
        return layout_home_month_language[mon][language_id_get()];
}
#endif
