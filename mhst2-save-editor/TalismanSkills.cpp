
#include "TalismanSkills.h"

const std::array<const char*, 316> SkillNames = {
	"3000 Health S",
	"3001 Health M",
	"3002 Health L",
	"3003 Health XL",
	"3004 N/A",
	"3005 Critical S",
	"3006 Critical M",
	"3007 Critical L",
	"3008 Critical XL",
	"3009 N/A",
	"3010 Evasion S",
	"3011 Evasion M",
	"3012 Evasion L",
	"3013 Evasion XL",
	"3014 N/A",
	"3015 Tenacity",
	"3016 N/A",
	"3017 Quick",
	"3018 N/A",
	"3019 Protection S",
	"3020 Protection M",
	"3021 Protection L",
	"3022 Protection XL",
	"3023 N/A",
	"3024 Nesting S",
	"3025 Nesting M",
	"3026 Nesting L",
	"3027 Nesting XL",
	"3028 N/A",
	"3029 (No Name)Non-Elem Atk Boost S",
	"3030 (No Name)Non-Elem Atk Boost M",
	"3031 (No Name)Non-Elem Atk Boost L",
	"3032 (No Name)Non-Elem Atk Boost XL",
	"3033 N/A",
	"3034 (No Name)Fire Boost S",
	"3035 (No Name)Fire Boost M",
	"3036 (No Name)Fire Boost L",
	"3037 (No Name)Fire Boost XL",
	"3038 N/A",
	"3039 (No Name)Water Boost S",
	"3040 (No Name)Water Boost M",
	"3041 (No Name)Water Boost L",
	"3042 (No Name)Water Boost XL",
	"3043 N/A",
	"3044 (No Name)Thunder Boost S",
	"3045 (No Name)Thunder Boost M",
	"3046 (No Name)Thunder Boost L",
	"3047 (No Name)Thunder Boost XL",
	"3048 N/A",
	"3049 (No Name)Ice Boost S",
	"3050 (No Name)Ice Boost M",
	"3051 (No Name)Ice Boost L",
	"3052 (No Name)Ice Boost XL",
	"3053 N/A",
	"3054 (No Name)Dragon Boost S",
	"3055 (No Name)Dragon Boost M",
	"3056 (No Name)Dragon Boost L",
	"3057 (No Name)Dragon Boost XL",
	"3058 N/A",
	"3059 (No Name)Non-Elem Def Boost S",
	"3060 (No Name)Non-Elem Def Boost M",
	"3061 (No Name)Non-Elem Def Boost L",
	"3062 (No Name)Non-Elem Def Boost XL",
	"3063 N/A",
	"3064 (No Name)Fire Def Boost S",
	"3065 (No Name)Fire Def Boost M",
	"3066 (No Name)Fire Def Boost L",
	"3067 (No Name)Fire Def Boost XL",
	"3068 N/A",
	"3069 (No Name)Water Def Boost S",
	"3070 (No Name)Water Def Boost M",
	"3071 (No Name)Water Def Boost L",
	"3072 (No Name)Water Def Boost XL",
	"3073 N/A",
	"3074 (No Name)Thunder Def Boost S",
	"3075 (No Name)Thunder Def Boost M",
	"3076 (No Name)Thunder Def Boost L",
	"3077 (No Name)Thunder Def Boost XL",
	"3078 N/A",
	"3079 (No Name)Ice Def Boost S",
	"3080 (No Name)Ice Def Boost M",
	"3081 (No Name)Ice Def Boost L",
	"3082 (No Name)Ice Def Boost XL",
	"3083 N/A",
	"3084 (No Name)Dragon Def Boost S",
	"3085 (No Name)Dragon Def Boost M",
	"3086 (No Name)Dragon Def Boost L",
	"3087 (No Name)Dragon Def Boost XL",
	"3088 N/A",
	"3089 All-Res S",
	"3090 All-Res M",
	"3091 All-Res L",
	"3092 All-Res XL",
	"3093 N/A",
	"3094 N/A",
	"3095 N/A",
	"3096 Potent S",
	"3097 Potent M",
	"3098 Potent L",
	"3099 Potent XL",
	"3100 N/A",
	"3101 Hounding S",
	"3102 Hounding M",
	"3103 Hounding L",
	"3104 Hounding XL",
	"3105 N/A",
	"3106 Cold Res",
	"3107 N/A",
	"3108 Heat Res",
	"3109 N/A",
	"3110 Anti 1-Hit KO",
	"3111 N/A",
	"3112 Antivenom S",
	"3113 Antivenom M",
	"3114 Antivenom L",
	"3115 Antivenom XL",
	"3116 N/A",
	"3117 Antiburn S",
	"3118 Antiburn M",
	"3119 Antiburn L",
	"3120 Antiburn XL",
	"3121 N/A",
	"3122 Antishock S",
	"3123 Antishock M",
	"3124 Antishock L",
	"3125 Antishock XL",
	"3126 N/A",
	"3127 Antisleep S",
	"3128 Antisleep M",
	"3129 Antisleep L",
	"3130 Antisleep XL",
	"3131 N/A",
	"3132 Antistench S",
	"3133 Antistench M",
	"3134 Antistench L",
	"3135 Antistench XL",
	"3136 N/A",
	"3137 Antiseal S",
	"3138 Antiseal M",
	"3139 Antiseal L",
	"3140 Antiseal XL",
	"3141 N/A",
	"3142 Dampening S",
	"3143 Dampening M",
	"3144 Dampening L",
	"3145 Dampening XL",
	"3146 N/A",
	"3147 Antibleed S",
	"3148 Antibleed M",
	"3149 Antibleed L",
	"3150 Antibleed XL",
	"3151 N/A",
	"3152 Antiblind S",
	"3153 Antiblind M",
	"3154 Antiblind L",
	"3155 Antiblind XL",
	"3156 N/A",
	"3157 Antistatus S",
	"3158 Antistatus M",
	"3159 Antistatus L",
	"3160 Antistatus XL",
	"3161 N/A",
	"3162 Kinship S",
	"3163 Kinship M",
	"3164 Kinship L",
	"3165 Kinship XL",
	"3166 N/A",
	"3167 Command S",
	"3168 Command M",
	"3169 Command L",
	"3170 Command XL",
	"3171 N/A",
	"3172 Head-On S",
	"3173 Head-On M",
	"3174 Head-On L",
	"3175 Head-On XL",
	"3176 N/A",
	"3177 All-Out S",
	"3178 All-Out M",
	"3179 All-Out L",
	"3180 All-Out XL",
	"3181 N/A",
	"3182 Showdown S",
	"3183 Showdown M",
	"3184 Showdown L",
	"3185 Showdown XL",
	"3186 N/A",
	"3187 Flinch S",
	"3188 Flinch M",
	"3189 Flinch L",
	"3190 Flinch XL",
	"3191 N/A",
	"3192 Bonding S",
	"3193 Bonding M",
	"3194 Bonding L",
	"3195 Bonding XL",
	"3196 N/A",
	"3197 Rapport S",
	"3198 Rapport M",
	"3199 Rapport L",
	"3200 Rapport XL",
	"3201 N/A",
	"3202 Bomber S",
	"3203 Bomber M",
	"3204 Bomber L",
	"3205 Bomber XL",
	"3206 N/A",
	"3207 Revival S",
	"3208 Revival M",
	"3209 Revival L",
	"3210 Revival XL",
	"3211 N/A",
	"3212 Guard-Heal S",
	"3213 Guard-Heal M",
	"3214 Guard-Heal L",
	"3215 Guard-Heal XL",
	"3216 N/A",
	"3217 Unscathed S",
	"3218 Unscathed M",
	"3219 Unscathed L",
	"3220 Unscathed XL",
	"3221 N/A",
	"3222 Hero S",
	"3223 Hero M",
	"3224 Hero L",
	"3225 Hero XL",
	"3226 N/A",
	"3227 Potential S",
	"3228 Potential M",
	"3229 Potential L",
	"3230 Potential XL",
	"3231 N/A",
	"3232 Escape S",
	"3233 Escape M",
	"3234 Escape L",
	"3235 Escape XL",
	"3236 N/A",
	"3237 Timely S",
	"3238 Timely M",
	"3239 Timely L",
	"3240 Timely XL",
	"3241 N/A",
	"3242 Partner S",
	"3243 Partner M",
	"3244 Partner L",
	"3245 Partner XL",
	"3246 N/A",
	"3247 Crit-Heal S",
	"3248 Crit-Heal M",
	"3249 Crit-Heal L",
	"3250 Crit-Heal XL",
	"3251 N/A",
	"3252 Crit-Kin S",
	"3253 Crit-Kin M",
	"3254 Crit-Kin L",
	"3255 Crit-Kin XL",
	"3256 N/A",
	"3257 Fortify S",
	"3258 Fortify M",
	"3259 Fortify L",
	"3260 Fortify XL",
	"3261 N/A",
	"3262 Saver S",
	"3263 Saver M",
	"3264 Saver L",
	"3265 Saver XL",
	"3266 N/A",
	"3267 Breaker S",
	"3268 Breaker M",
	"3269 Breaker L",
	"3270 Breaker XL",
	"3271 N/A",
	"3272 Counter S",
	"3273 Counter M",
	"3274 Counter L",
	"3275 Counter XL",
	"3276 N/A",
	"3277 Draw S",
	"3278 Draw M",
	"3279 Draw L",
	"3280 Draw XL",
	"3281 N/A",
	"3282 Thrust S",
	"3283 Thrust M",
	"3284 Thrust L",
	"3285 Thrust XL",
	"3286 N/A",
	"3287 Sonorous S",
	"3288 Sonorous M",
	"3289 Sonorous L",
	"3290 Sonorous XL",
	"3291 N/A",
	"3292 Capacity S",
	"3293 Capacity M",
	"3294 Capacity L",
	"3295 Capacity XL",
	"3296 N/A",
	"3297 Marksman S",
	"3298 Marksman M",
	"3299 Marksman L",
	"3300 Marksman XL",
	"3301 N/A",
	"3302 Furyslash S",
	"3303 Furyslash M",
	"3304 Furyslash L",
	"3305 Furyslash XL",
	"3306 N/A",
	"3307 Furybash S",
	"3308 Furybash M",
	"3309 Furybash L",
	"3310 Furybash XL",
	"3311 N/A",
	"3312 Weak Pt S",
	"3313 Weak Pt M",
	"3314 Weak Pt L",
	"3315 Weak Pt XL",
};
