#include "common/language.h"
typedef enum
{
    LAYOUT_SECURITY_LANG_ID_LANG_HEAD,
    LAYOUT_SECURITY_LANG_ID_LANG_TIP,
    LAYOUT_SECURITY_LANG_ID_LANG_AUTO_RECORD,
    LAYOUT_SECURITY_LANG_ID_LANG_RUN,
    LAYOUT_SECURITY_LANG_ID_LANG_END,
    LAYOUT_SECURITY_LANG_ID_LANG_EXECUTION,
    LAYOUT_SECURITY_LANG_ID_LANG_ENTER_PASSSWORD,
    LAYOUT_SECURITY_LANG_ID_LANG_SENSOR1,
    LAYOUT_SECURITY_LANG_ID_LANG_SENSOR2,
    LAYOUT_SECURITY_LANG_ID_LANG_SENSOR3,
    LAYOUT_SECURITY_LANG_ID_LANG_SENSOR4,
    LAYOUT_SECURITY_LANG_ID_LANG_SENSOR5,
    LAYOUT_SECURITY_LANG_ID_LANG_SENSOR6,
    LAYOUT_SECURITY_LANG_ID_LANG_SENSOR7,
    LAYOUT_SECURITY_LANG_ID_LANG_SENSOR8,
    LAYOUT_SECURITY_LANG_ID_LANG_TOTAL
} LAYOUT_SECURITY_LANG_ID;

static const char *layout_security_general_language[LAYOUT_SECURITY_LANG_ID_LANG_TOTAL][LANGUAGE_ID_TOTAL] =
    {
        {"방범","保安","Security","Безопасность","Seguridad","An ninh","حماية"},
        {
            "집 안에 있을 때 외부 침입을 감지합니다.",
            "当您在家里时，检测外部入侵",
            "Detect outside intrusion when you are inside home",
            "Сигнализатор проникновения",
            "Detecta intrusiones externas cuando estás dentro de casa",
            "Phát hiện xâm nhập từ bên ngoài khi bạn đang trong nhà",
            "كشف التسلل الخارجي عندما تكون داخل المنزل",
        },
        {
            "비상 CCTV 자동녹화",
            "紧急CCTV自动录像",
            "CCTV automatic recording",
            "Автоматическое сохранение видеоизображения",
            "Grabación automática de CCTV",
            "CCTV tự động ghi hình",
            "تسجيل أوتوماتيكي CCTV"
        },
        {
            "방범 기능이 실행 중입니다.",
            "安全功能正在运行",
            "Security mode is running",
            "Режим безопасности запущен",
            "Modo de seguridad se está ejecutando",
            "Chế độ an ninh đang hoạt động",
            "وضع الأمان قيد التشغيل"

        },

        {"종료", "结束", "End","thúc","Fin","Kết","إنهاء"},
        
        {"실행", "执行", "Execution","Выполнение","Ejecución","Thực hiện","تنفيذ"},

        {"비밀번호 입력","输入密码","Enter Password","Введите пароль","Introducir contraseña","Nhập mật khẩu","أدخل كلمة المرور"},
    {
        "방범구역\n센서 1",
        "防止犯罪区域\nsensor 1",
        "security area\nsensor 1",
        "зоны безопасности\nДатчик 1"
        "de zona de seguridad\nSensor1 "
        "an ninh khu vực\nCảm biến 1"
        " منطقة الأمان\nمستشعر 1"
    },
    {
        "방범구역\n센서 2",
        "防止犯罪区域\nsensor 2",
        "security area\nsensor 2",
        "зоны безопасности\nДатчик 2"
        "de zona de seguridad\nSensor 2 "
        "an ninh khu vực\nCảm biến 2"
        " منطقة الأمان\nمستشعر 2"
    },
    {
        "방범구역\n센서 3",
        "防止犯罪区域\nsensor 3",
        "security area\nsensor 3",
        "зоны безопасности\nДатчик 3"
        "de zona de seguridad\nSensor 3 "
        "an ninh khu vực\nCảm biến 3"
        " منطقة الأمان\nمستشعر 3"
    },
    {
        "방범구역\n센서 4",
        "防止犯罪区域\nsensor 4",
        "security area\nsensor 4",
        "зоны безопасности\nДатчик 4"
        "de zona de seguridad\nSensor 4"
        "an ninh khu vực\nCảm biến 4"
        " منطقة الأمان\nمستشعر 4"
    },
    {
        "방범구역\n센서 5",
        "防止犯罪区域\nsensor 5",
        "security area\nsensor 5",
        "зоны безопасности\nДатчик 5"
        "de zona de seguridad\nSensor 5 "
        "an ninh khu vực\nCảm biến 5"
        " منطقة الأمان\nمستشعر 5"
    },
    {
        "방범구역\n센서 6",
        "防止犯罪区域\nsensor 6",
        "security area\nsensor 6",
        "зоны безопасности\nДатчик 6"
        "de zona de seguridad\nSensor 6 "
        "an ninh khu vực\nCảm biến 6"
        " منطقة الأمان\nمستشعر 6"
    },
    {
        "방범구역\n센서 7",
        "防止犯罪区域\nsensor 7",
        "security area\nsensor 7",
        "зоны безопасности\nДатчик 7"
        "de zona de seguridad\nSensor 7"
        "an ninh khu vực\nCảm biến 7"
        " منطقة الأمان\nمستشعر 7"
    },

};


static inline const char *layout_security_language_get(int id)
{
    return layout_security_general_language[id][language_id_get()];
}