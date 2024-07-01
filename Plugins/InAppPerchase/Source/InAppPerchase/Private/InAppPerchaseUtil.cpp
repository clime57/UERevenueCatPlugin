#include "InAppPerchaseUtil.h"


#if PLATFORM_VISIONOS || PLATFORM_IOS

NSString* ConvertFString(const FString UEString) {
    if (!UEString.IsEmpty())
        return [NSString stringWithUTF8String : TCHAR_TO_ANSI(*UEString)];
    else
        return nil;
}


TArray<FString> ConvertNSSetToTArray(NSSet<NSString *> * _Nonnull stringSet) {
    TArray<FString> result;
  
    // 遍历 NSSet 中的所有元素
    for (NSString *obj in stringSet) {
        // 将 NSString 转换为 FString
        FString fstring(UTF8_TO_TCHAR(obj.UTF8String));
        // 将 FString 添加到结果数组中
        result.Emplace(fstring);
    }

    // 返回转换后的 TArray<FString>
    return result;
}

FDateTime ConvertNSDateToFDateTime(NSDate* date) {
    if (!date) {
        // 如果date为nil，返回一个无效的FDateTime
        return FDateTime::MinValue();
    }
  
    // 获取NSTimeInterval（自1970年1月1日以来的秒数）
    NSTimeInterval timeInterval = [date timeIntervalSince1970];
  
    // 将秒数转换为毫秒（FDateTime以毫秒为单位）
    int64_t milliseconds = static_cast<int64_t>(timeInterval * 1000.0);
  
    // 创建一个FDateTime对象，使用从1970年1月1日以来的毫秒数
    FDateTime result(milliseconds);
  
    // 返回转换后的FDateTime
    return result;
}

FString ConvertNSURLToFString(NSURL* url) {
    if (!url) {
        return FString(); // 返回一个空的FString
    }
  
    // 获取NSURL的字符串表示（假设我们想要完整的URL）
    NSString* urlString = [url absoluteString];
  
    // 将NSString转换为C字符串（UTF-8编码）
    const char* utf8String = [urlString UTF8String];
  
    // 将C字符串转换为FString
    FString result(utf8String);
  
    // 返回转换后的FString
    return result;
}

TMap<FString, FString> ConvertNSDictionaryToTMap(NSDictionary<NSString *, NSString *> *dictionary) {
    TMap<FString, FString> result;
      
    if (dictionary) {
        for (NSString *key in dictionary) {
            NSString *value = dictionary[key];
              
            // 将 NSString 转换为 FString
            FString fstringKey(key.UTF8String);
            FString fstringValue(value.UTF8String);
              
            // 将键值对添加到 TMap 中
            result.Add(fstringKey, fstringValue);
        }
    }
      
    return result;
}



#endif
