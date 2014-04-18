#include "WindowUtil.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Diagnostics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Runtime::InteropServices;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;
namespace MeGUI
{
	namespace core
	{
		namespace util
		{

			std::string WindowUtil::GetText(IntPtr hWnd)
			{
				// Allocate correct string length first
				int length = GetWindowTextLength(hWnd);
				StringBuilder *sb = new StringBuilder(length + 1);
				GetWindowText(hWnd, sb, sb->Capacity);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				return sb->ToString();
			}

			void WindowUtil::PreventSystemPowerdown()
			{
				SetThreadExecutionState(ES_SYSTEM_REQUIRED | ES_CONTINUOUS);
			}

			void WindowUtil::AllowSystemPowerdown()
			{
				SetThreadExecutionState(ES_CONTINUOUS);
			}

			std::string WindowUtil::GetErrorText(int iErrorValue)
			{
				if (iErrorValue >= 0)
					return StringConverterHelper::toString(iErrorValue);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
				std::string strErrorHex = iErrorValue.ToString("X");
				std::string strErrorText = "";

				// http://msdn.microsoft.com/en-us/library/cc704588%28v=prot.10%29.aspx
				// http://nologs.com/ntstatus.html
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//				switch (strErrorHex)
//ORIGINAL LINE: case "00000000":
				if (strErrorHex == "00000000")
				{
						strErrorText = "STATUS_SUCCESS";
				}
//ORIGINAL LINE: case "00000001":
				else if (strErrorHex == "00000001")
				{
						strErrorText = "STATUS_WAIT_1";
				}
//ORIGINAL LINE: case "00000002":
				else if (strErrorHex == "00000002")
				{
						strErrorText = "STATUS_WAIT_2";
				}
//ORIGINAL LINE: case "00000003":
				else if (strErrorHex == "00000003")
				{
						strErrorText = "STATUS_WAIT_3";
				}
//ORIGINAL LINE: case "0000003F":
				else if (strErrorHex == "0000003F")
				{
						strErrorText = "STATUS_WAIT_63";
				}
//ORIGINAL LINE: case "00000080":
				else if (strErrorHex == "00000080")
				{
						strErrorText = "STATUS_ABANDONED";
				}
//ORIGINAL LINE: case "000000BF":
				else if (strErrorHex == "000000BF")
				{
						strErrorText = "STATUS_ABANDONED_WAIT_63";
				}
//ORIGINAL LINE: case "000000C0":
				else if (strErrorHex == "000000C0")
				{
						strErrorText = "STATUS_USER_APC";
				}
//ORIGINAL LINE: case "00000100":
				else if (strErrorHex == "00000100")
				{
						strErrorText = "STATUS_KERNEL_APC";
				}
//ORIGINAL LINE: case "00000101":
				else if (strErrorHex == "00000101")
				{
						strErrorText = "STATUS_ALERTED";
				}
//ORIGINAL LINE: case "00000102":
				else if (strErrorHex == "00000102")
				{
						strErrorText = "STATUS_TIMEOUT";
				}
//ORIGINAL LINE: case "00000103":
				else if (strErrorHex == "00000103")
				{
						strErrorText = "STATUS_PENDING";
				}
//ORIGINAL LINE: case "00000104":
				else if (strErrorHex == "00000104")
				{
						strErrorText = "STATUS_REPARSE";
				}
//ORIGINAL LINE: case "00000105":
				else if (strErrorHex == "00000105")
				{
						strErrorText = "STATUS_MORE_ENTRIES";
				}
//ORIGINAL LINE: case "00000106":
				else if (strErrorHex == "00000106")
				{
						strErrorText = "STATUS_NOT_ALL_ASSIGNED";
				}
//ORIGINAL LINE: case "00000107":
				else if (strErrorHex == "00000107")
				{
						strErrorText = "STATUS_SOME_NOT_MAPPED";
				}
//ORIGINAL LINE: case "00000108":
				else if (strErrorHex == "00000108")
				{
						strErrorText = "STATUS_OPLOCK_BREAK_IN_PROGRESS";
				}
//ORIGINAL LINE: case "00000109":
				else if (strErrorHex == "00000109")
				{
						strErrorText = "STATUS_VOLUME_MOUNTED";
				}
//ORIGINAL LINE: case "0000010A":
				else if (strErrorHex == "0000010A")
				{
						strErrorText = "STATUS_RXACT_COMMITTED";
				}
//ORIGINAL LINE: case "0000010B":
				else if (strErrorHex == "0000010B")
				{
						strErrorText = "STATUS_NOTIFY_CLEANUP";
				}
//ORIGINAL LINE: case "0000010C":
				else if (strErrorHex == "0000010C")
				{
						strErrorText = "STATUS_NOTIFY_ENUM_DIR";
				}
//ORIGINAL LINE: case "0000010D":
				else if (strErrorHex == "0000010D")
				{
						strErrorText = "STATUS_NO_QUOTAS_FOR_ACCOUNT";
				}
//ORIGINAL LINE: case "0000010E":
				else if (strErrorHex == "0000010E")
				{
						strErrorText = "STATUS_PRIMARY_TRANSPORT_CONNECT_FAILED";
				}
//ORIGINAL LINE: case "00000110":
				else if (strErrorHex == "00000110")
				{
						strErrorText = "STATUS_PAGE_FAULT_TRANSITION";
				}
//ORIGINAL LINE: case "00000111":
				else if (strErrorHex == "00000111")
				{
						strErrorText = "STATUS_PAGE_FAULT_DEMAND_ZERO";
				}
//ORIGINAL LINE: case "00000112":
				else if (strErrorHex == "00000112")
				{
						strErrorText = "STATUS_PAGE_FAULT_COPY_ON_WRITE";
				}
//ORIGINAL LINE: case "00000113":
				else if (strErrorHex == "00000113")
				{
						strErrorText = "STATUS_PAGE_FAULT_GUARD_PAGE";
				}
//ORIGINAL LINE: case "00000114":
				else if (strErrorHex == "00000114")
				{
						strErrorText = "STATUS_PAGE_FAULT_PAGING_FILE";
				}
//ORIGINAL LINE: case "00000115":
				else if (strErrorHex == "00000115")
				{
						strErrorText = "STATUS_CACHE_PAGE_LOCKED";
				}
//ORIGINAL LINE: case "00000116":
				else if (strErrorHex == "00000116")
				{
						strErrorText = "STATUS_CRASH_DUMP";
				}
//ORIGINAL LINE: case "00000117":
				else if (strErrorHex == "00000117")
				{
						strErrorText = "STATUS_BUFFER_ALL_ZEROS";
				}
//ORIGINAL LINE: case "00000118":
				else if (strErrorHex == "00000118")
				{
						strErrorText = "STATUS_REPARSE_OBJECT";
				}
//ORIGINAL LINE: case "00000119":
				else if (strErrorHex == "00000119")
				{
						strErrorText = "STATUS_RESOURCE_REQUIREMENTS_CHANGED";
				}
//ORIGINAL LINE: case "00000120":
				else if (strErrorHex == "00000120")
				{
						strErrorText = "STATUS_TRANSLATION_COMPLETE";
				}
//ORIGINAL LINE: case "00000121":
				else if (strErrorHex == "00000121")
				{
						strErrorText = "STATUS_DS_MEMBERSHIP_EVALUATED_LOCALLY";
				}
//ORIGINAL LINE: case "00000122":
				else if (strErrorHex == "00000122")
				{
						strErrorText = "STATUS_NOTHING_TO_TERMINATE";
				}
//ORIGINAL LINE: case "00000123":
				else if (strErrorHex == "00000123")
				{
						strErrorText = "STATUS_PROCESS_NOT_IN_JOB";
				}
//ORIGINAL LINE: case "00000124":
				else if (strErrorHex == "00000124")
				{
						strErrorText = "STATUS_PROCESS_IN_JOB";
				}
//ORIGINAL LINE: case "00000125":
				else if (strErrorHex == "00000125")
				{
						strErrorText = "STATUS_VOLSNAP_HIBERNATE_READY";
				}
//ORIGINAL LINE: case "00000126":
				else if (strErrorHex == "00000126")
				{
						strErrorText = "STATUS_FSFILTER_OP_COMPLETED_SUCCESSFULLY";
				}
//ORIGINAL LINE: case "00010001":
				else if (strErrorHex == "00010001")
				{
						strErrorText = "DBG_EXCEPTION_HANDLED";
				}
//ORIGINAL LINE: case "00010002":
				else if (strErrorHex == "00010002")
				{
						strErrorText = "DBG_CONTINUE";
				}
//ORIGINAL LINE: case "40000000":
				else if (strErrorHex == "40000000")
				{
						strErrorText = "STATUS_OBJECT_NAME_EXISTS";
				}
//ORIGINAL LINE: case "40000001":
				else if (strErrorHex == "40000001")
				{
						strErrorText = "STATUS_THREAD_WAS_SUSPENDED";
				}
//ORIGINAL LINE: case "40000002":
				else if (strErrorHex == "40000002")
				{
						strErrorText = "STATUS_WORKING_SET_LIMIT_RANGE";
				}
//ORIGINAL LINE: case "40000003":
				else if (strErrorHex == "40000003")
				{
						strErrorText = "STATUS_IMAGE_NOT_AT_BASE";
				}
//ORIGINAL LINE: case "40000004":
				else if (strErrorHex == "40000004")
				{
						strErrorText = "STATUS_RXACT_STATE_CREATED";
				}
//ORIGINAL LINE: case "40000005":
				else if (strErrorHex == "40000005")
				{
						strErrorText = "STATUS_SEGMENT_NOTIFICATION";
				}
//ORIGINAL LINE: case "40000006":
				else if (strErrorHex == "40000006")
				{
						strErrorText = "STATUS_LOCAL_USER_SESSION_KEY";
				}
//ORIGINAL LINE: case "40000007":
				else if (strErrorHex == "40000007")
				{
						strErrorText = "STATUS_BAD_CURRENT_DIRECTORY";
				}
//ORIGINAL LINE: case "40000008":
				else if (strErrorHex == "40000008")
				{
						strErrorText = "STATUS_SERIAL_MORE_WRITES";
				}
//ORIGINAL LINE: case "40000009":
				else if (strErrorHex == "40000009")
				{
						strErrorText = "STATUS_REGISTRY_RECOVERED";
				}
//ORIGINAL LINE: case "4000000A":
				else if (strErrorHex == "4000000A")
				{
						strErrorText = "STATUS_FT_READ_RECOVERY_FROM_BACKUP";
				}
//ORIGINAL LINE: case "4000000B":
				else if (strErrorHex == "4000000B")
				{
						strErrorText = "STATUS_FT_WRITE_RECOVERY";
				}
//ORIGINAL LINE: case "4000000C":
				else if (strErrorHex == "4000000C")
				{
						strErrorText = "STATUS_SERIAL_COUNTER_TIMEOUT";
				}
//ORIGINAL LINE: case "4000000D":
				else if (strErrorHex == "4000000D")
				{
						strErrorText = "STATUS_NULL_LM_PASSWORD";
				}
//ORIGINAL LINE: case "4000000E":
				else if (strErrorHex == "4000000E")
				{
						strErrorText = "STATUS_IMAGE_MACHINE_TYPE_MISMATCH";
				}
//ORIGINAL LINE: case "4000000F":
				else if (strErrorHex == "4000000F")
				{
						strErrorText = "STATUS_RECEIVE_PARTIAL";
				}
//ORIGINAL LINE: case "40000010":
				else if (strErrorHex == "40000010")
				{
						strErrorText = "STATUS_RECEIVE_EXPEDITED";
				}
//ORIGINAL LINE: case "40000011":
				else if (strErrorHex == "40000011")
				{
						strErrorText = "STATUS_RECEIVE_PARTIAL_EXPEDITED";
				}
//ORIGINAL LINE: case "40000012":
				else if (strErrorHex == "40000012")
				{
						strErrorText = "STATUS_EVENT_DONE";
				}
//ORIGINAL LINE: case "40000013":
				else if (strErrorHex == "40000013")
				{
						strErrorText = "STATUS_EVENT_PENDING";
				}
//ORIGINAL LINE: case "40000014":
				else if (strErrorHex == "40000014")
				{
						strErrorText = "STATUS_CHECKING_FILE_SYSTEM";
				}
//ORIGINAL LINE: case "40000015":
				else if (strErrorHex == "40000015")
				{
						strErrorText = "STATUS_FATAL_APP_EXIT";
				}
//ORIGINAL LINE: case "40000016":
				else if (strErrorHex == "40000016")
				{
						strErrorText = "STATUS_PREDEFINED_HANDLE";
				}
//ORIGINAL LINE: case "40000017":
				else if (strErrorHex == "40000017")
				{
						strErrorText = "STATUS_WAS_UNLOCKED";
				}
//ORIGINAL LINE: case "40000018":
				else if (strErrorHex == "40000018")
				{
						strErrorText = "STATUS_SERVICE_NOTIFICATION";
				}
//ORIGINAL LINE: case "40000019":
				else if (strErrorHex == "40000019")
				{
						strErrorText = "STATUS_WAS_LOCKED";
				}
//ORIGINAL LINE: case "4000001A":
				else if (strErrorHex == "4000001A")
				{
						strErrorText = "STATUS_LOG_HARD_ERROR";
				}
//ORIGINAL LINE: case "4000001B":
				else if (strErrorHex == "4000001B")
				{
						strErrorText = "STATUS_ALREADY_WIN32";
				}
//ORIGINAL LINE: case "4000001C":
				else if (strErrorHex == "4000001C")
				{
						strErrorText = "STATUS_WX86_UNSIMULATE";
				}
//ORIGINAL LINE: case "4000001D":
				else if (strErrorHex == "4000001D")
				{
						strErrorText = "STATUS_WX86_CONTINUE";
				}
//ORIGINAL LINE: case "4000001E":
				else if (strErrorHex == "4000001E")
				{
						strErrorText = "STATUS_WX86_SINGLE_STEP";
				}
//ORIGINAL LINE: case "4000001F":
				else if (strErrorHex == "4000001F")
				{
						strErrorText = "STATUS_WX86_BREAKPOINT";
				}
//ORIGINAL LINE: case "40000020":
				else if (strErrorHex == "40000020")
				{
						strErrorText = "STATUS_WX86_EXCEPTION_CONTINUE";
				}
//ORIGINAL LINE: case "40000021":
				else if (strErrorHex == "40000021")
				{
						strErrorText = "STATUS_WX86_EXCEPTION_LASTCHANCE";
				}
//ORIGINAL LINE: case "40000022":
				else if (strErrorHex == "40000022")
				{
						strErrorText = "STATUS_WX86_EXCEPTION_CHAIN";
				}
//ORIGINAL LINE: case "40000023":
				else if (strErrorHex == "40000023")
				{
						strErrorText = "STATUS_IMAGE_MACHINE_TYPE_MISMATCH_EXE";
				}
//ORIGINAL LINE: case "40000024":
				else if (strErrorHex == "40000024")
				{
						strErrorText = "STATUS_NO_YIELD_PERFORMED";
				}
//ORIGINAL LINE: case "40000025":
				else if (strErrorHex == "40000025")
				{
						strErrorText = "STATUS_TIMER_RESUME_IGNORED";
				}
//ORIGINAL LINE: case "40000026":
				else if (strErrorHex == "40000026")
				{
						strErrorText = "STATUS_ARBITRATION_UNHANDLED";
				}
//ORIGINAL LINE: case "40000027":
				else if (strErrorHex == "40000027")
				{
						strErrorText = "STATUS_CARDBUS_NOT_SUPPORTED";
				}
//ORIGINAL LINE: case "40000028":
				else if (strErrorHex == "40000028")
				{
						strErrorText = "STATUS_WX86_CREATEWX86TIB";
				}
//ORIGINAL LINE: case "40000029":
				else if (strErrorHex == "40000029")
				{
						strErrorText = "STATUS_MP_PROCESSOR_MISMATCH";
				}
//ORIGINAL LINE: case "4000002A":
				else if (strErrorHex == "4000002A")
				{
						strErrorText = "STATUS_HIBERNATED";
				}
//ORIGINAL LINE: case "4000002B":
				else if (strErrorHex == "4000002B")
				{
						strErrorText = "STATUS_RESUME_HIBERNATION";
				}
//ORIGINAL LINE: case "4000002C":
				else if (strErrorHex == "4000002C")
				{
						strErrorText = "STATUS_FIRMWARE_UPDATED";
				}
//ORIGINAL LINE: case "4000002D":
				else if (strErrorHex == "4000002D")
				{
						strErrorText = "STATUS_DRIVERS_LEAKING_LOCKED_PAGES";
				}
//ORIGINAL LINE: case "40010001":
				else if (strErrorHex == "40010001")
				{
						strErrorText = "DBG_REPLY_LATER";
				}
//ORIGINAL LINE: case "40010002":
				else if (strErrorHex == "40010002")
				{
						strErrorText = "DBG_UNABLE_TO_PROVIDE_HANDLE";
				}
//ORIGINAL LINE: case "40010003":
				else if (strErrorHex == "40010003")
				{
						strErrorText = "DBG_TERMINATE_THREAD";
				}
//ORIGINAL LINE: case "40010004":
				else if (strErrorHex == "40010004")
				{
						strErrorText = "DBG_TERMINATE_PROCESS";
				}
//ORIGINAL LINE: case "40010005":
				else if (strErrorHex == "40010005")
				{
						strErrorText = "DBG_CONTROL_C";
				}
//ORIGINAL LINE: case "40010006":
				else if (strErrorHex == "40010006")
				{
						strErrorText = "DBG_PRINTEXCEPTION_C";
				}
//ORIGINAL LINE: case "40010007":
				else if (strErrorHex == "40010007")
				{
						strErrorText = "DBG_RIPEXCEPTION";
				}
//ORIGINAL LINE: case "40010008":
				else if (strErrorHex == "40010008")
				{
						strErrorText = "DBG_CONTROL_BREAK";
				}
//ORIGINAL LINE: case "40010009":
				else if (strErrorHex == "40010009")
				{
						strErrorText = "DBG_COMMAND_EXCEPTION";
				}
//ORIGINAL LINE: case "80000001":
				else if (strErrorHex == "80000001")
				{
						strErrorText = "STATUS_GUARD_PAGE_VIOLATION";
				}
//ORIGINAL LINE: case "80000002":
				else if (strErrorHex == "80000002")
				{
						strErrorText = "STATUS_DATATYPE_MISALIGNMENT";
				}
//ORIGINAL LINE: case "80000003":
				else if (strErrorHex == "80000003")
				{
						strErrorText = "STATUS_BREAKPOINT";
				}
//ORIGINAL LINE: case "80000004":
				else if (strErrorHex == "80000004")
				{
						strErrorText = "STATUS_SINGLE_STEP";
				}
//ORIGINAL LINE: case "80000005":
				else if (strErrorHex == "80000005")
				{
						strErrorText = "STATUS_BUFFER_OVERFLOW";
				}
//ORIGINAL LINE: case "80000006":
				else if (strErrorHex == "80000006")
				{
						strErrorText = "STATUS_NO_MORE_FILES";
				}
//ORIGINAL LINE: case "80000007":
				else if (strErrorHex == "80000007")
				{
						strErrorText = "STATUS_WAKE_SYSTEM_DEBUGGER";
				}
//ORIGINAL LINE: case "8000000A":
				else if (strErrorHex == "8000000A")
				{
						strErrorText = "STATUS_HANDLES_CLOSED";
				}
//ORIGINAL LINE: case "8000000B":
				else if (strErrorHex == "8000000B")
				{
						strErrorText = "STATUS_NO_INHERITANCE";
				}
//ORIGINAL LINE: case "8000000C":
				else if (strErrorHex == "8000000C")
				{
						strErrorText = "STATUS_GUID_SUBSTITUTION_MADE";
				}
//ORIGINAL LINE: case "8000000D":
				else if (strErrorHex == "8000000D")
				{
						strErrorText = "STATUS_PARTIAL_COPY";
				}
//ORIGINAL LINE: case "8000000E":
				else if (strErrorHex == "8000000E")
				{
						strErrorText = "STATUS_DEVICE_PAPER_EMPTY";
				}
//ORIGINAL LINE: case "8000000F":
				else if (strErrorHex == "8000000F")
				{
						strErrorText = "STATUS_DEVICE_POWERED_OFF";
				}
//ORIGINAL LINE: case "80000010":
				else if (strErrorHex == "80000010")
				{
						strErrorText = "STATUS_DEVICE_OFF_LINE";
				}
//ORIGINAL LINE: case "80000011":
				else if (strErrorHex == "80000011")
				{
						strErrorText = "STATUS_DEVICE_BUSY";
				}
//ORIGINAL LINE: case "80000012":
				else if (strErrorHex == "80000012")
				{
						strErrorText = "STATUS_NO_MORE_EAS";
				}
//ORIGINAL LINE: case "80000013":
				else if (strErrorHex == "80000013")
				{
						strErrorText = "STATUS_INVALID_EA_NAME";
				}
//ORIGINAL LINE: case "80000014":
				else if (strErrorHex == "80000014")
				{
						strErrorText = "STATUS_EA_LIST_INCONSISTENT";
				}
//ORIGINAL LINE: case "80000015":
				else if (strErrorHex == "80000015")
				{
						strErrorText = "STATUS_INVALID_EA_FLAG";
				}
//ORIGINAL LINE: case "80000016":
				else if (strErrorHex == "80000016")
				{
						strErrorText = "STATUS_VERIFY_REQUIRED";
				}
//ORIGINAL LINE: case "80000017":
				else if (strErrorHex == "80000017")
				{
						strErrorText = "STATUS_EXTRANEOUS_INFORMATION";
				}
//ORIGINAL LINE: case "80000018":
				else if (strErrorHex == "80000018")
				{
						strErrorText = "STATUS_RXACT_COMMIT_NECESSARY";
				}
//ORIGINAL LINE: case "8000001A":
				else if (strErrorHex == "8000001A")
				{
						strErrorText = "STATUS_NO_MORE_ENTRIES";
				}
//ORIGINAL LINE: case "8000001B":
				else if (strErrorHex == "8000001B")
				{
						strErrorText = "STATUS_FILEMARK_DETECTED";
				}
//ORIGINAL LINE: case "8000001C":
				else if (strErrorHex == "8000001C")
				{
						strErrorText = "STATUS_MEDIA_CHANGED";
				}
//ORIGINAL LINE: case "8000001D":
				else if (strErrorHex == "8000001D")
				{
						strErrorText = "STATUS_BUS_RESET";
				}
//ORIGINAL LINE: case "8000001E":
				else if (strErrorHex == "8000001E")
				{
						strErrorText = "STATUS_END_OF_MEDIA";
				}
//ORIGINAL LINE: case "8000001F":
				else if (strErrorHex == "8000001F")
				{
						strErrorText = "STATUS_BEGINNING_OF_MEDIA";
				}
//ORIGINAL LINE: case "80000020":
				else if (strErrorHex == "80000020")
				{
						strErrorText = "STATUS_MEDIA_CHECK";
				}
//ORIGINAL LINE: case "80000021":
				else if (strErrorHex == "80000021")
				{
						strErrorText = "STATUS_SETMARK_DETECTED";
				}
//ORIGINAL LINE: case "80000022":
				else if (strErrorHex == "80000022")
				{
						strErrorText = "STATUS_NO_DATA_DETECTED";
				}
//ORIGINAL LINE: case "80000023":
				else if (strErrorHex == "80000023")
				{
						strErrorText = "STATUS_REDIRECTOR_HAS_OPEN_HANDLES";
				}
//ORIGINAL LINE: case "80000024":
				else if (strErrorHex == "80000024")
				{
						strErrorText = "STATUS_SERVER_HAS_OPEN_HANDLES";
				}
//ORIGINAL LINE: case "80000025":
				else if (strErrorHex == "80000025")
				{
						strErrorText = "STATUS_ALREADY_DISCONNECTED";
				}
//ORIGINAL LINE: case "80000026":
				else if (strErrorHex == "80000026")
				{
						strErrorText = "STATUS_LONGJUMP";
				}
//ORIGINAL LINE: case "80000027":
				else if (strErrorHex == "80000027")
				{
						strErrorText = "STATUS_CLEANER_CARTRIDGE_INSTALLED";
				}
//ORIGINAL LINE: case "80000028":
				else if (strErrorHex == "80000028")
				{
						strErrorText = "STATUS_PLUGPLAY_QUERY_VETOED";
				}
//ORIGINAL LINE: case "80000029":
				else if (strErrorHex == "80000029")
				{
						strErrorText = "STATUS_UNWIND_CONSOLIDATE";
				}
//ORIGINAL LINE: case "8000002A":
				else if (strErrorHex == "8000002A")
				{
						strErrorText = "STATUS_REGISTRY_HIVE_RECOVERED";
				}
//ORIGINAL LINE: case "8000002B":
				else if (strErrorHex == "8000002B")
				{
						strErrorText = "STATUS_DLL_MIGHT_BE_INSECURE";
				}
//ORIGINAL LINE: case "8000002C":
				else if (strErrorHex == "8000002C")
				{
						strErrorText = "STATUS_DLL_MIGHT_BE_INCOMPATIBLE";
				}
//ORIGINAL LINE: case "80010001":
				else if (strErrorHex == "80010001")
				{
						strErrorText = "DBG_EXCEPTION_NOT_HANDLED";
				}
//ORIGINAL LINE: case "80130001":
				else if (strErrorHex == "80130001")
				{
						strErrorText = "STATUS_CLUSTER_NODE_ALREADY_UP";
				}
//ORIGINAL LINE: case "80130002":
				else if (strErrorHex == "80130002")
				{
						strErrorText = "STATUS_CLUSTER_NODE_ALREADY_DOWN";
				}
//ORIGINAL LINE: case "80130003":
				else if (strErrorHex == "80130003")
				{
						strErrorText = "STATUS_CLUSTER_NETWORK_ALREADY_ONLINE";
				}
//ORIGINAL LINE: case "80130004":
				else if (strErrorHex == "80130004")
				{
						strErrorText = "STATUS_CLUSTER_NETWORK_ALREADY_OFFLINE";
				}
//ORIGINAL LINE: case "80130005":
				else if (strErrorHex == "80130005")
				{
						strErrorText = "STATUS_CLUSTER_NODE_ALREADY_MEMBER";
				}
//ORIGINAL LINE: case "C0000001":
				else if (strErrorHex == "C0000001")
				{
						strErrorText = "STATUS_UNSUCCESSFUL";
				}
//ORIGINAL LINE: case "C0000002":
				else if (strErrorHex == "C0000002")
				{
						strErrorText = "STATUS_NOT_IMPLEMENTED";
				}
//ORIGINAL LINE: case "C0000003":
				else if (strErrorHex == "C0000003")
				{
						strErrorText = "STATUS_INVALID_INFO_CLASS";
				}
//ORIGINAL LINE: case "C0000004":
				else if (strErrorHex == "C0000004")
				{
						strErrorText = "STATUS_INFO_LENGTH_MISMATCH";
				}
//ORIGINAL LINE: case "C0000005":
				else if (strErrorHex == "C0000005")
				{
						strErrorText = "STATUS_ACCESS_VIOLATION";
				}
//ORIGINAL LINE: case "C0000006":
				else if (strErrorHex == "C0000006")
				{
						strErrorText = "STATUS_IN_PAGE_ERROR";
				}
//ORIGINAL LINE: case "C0000007":
				else if (strErrorHex == "C0000007")
				{
						strErrorText = "STATUS_PAGEFILE_QUOTA";
				}
//ORIGINAL LINE: case "C0000008":
				else if (strErrorHex == "C0000008")
				{
						strErrorText = "STATUS_INVALID_HANDLE";
				}
//ORIGINAL LINE: case "C0000009":
				else if (strErrorHex == "C0000009")
				{
						strErrorText = "STATUS_BAD_INITIAL_STACK";
				}
//ORIGINAL LINE: case "C000000A":
				else if (strErrorHex == "C000000A")
				{
						strErrorText = "STATUS_BAD_INITIAL_PC";
				}
//ORIGINAL LINE: case "C000000B":
				else if (strErrorHex == "C000000B")
				{
						strErrorText = "STATUS_INVALID_CID";
				}
//ORIGINAL LINE: case "C000000C":
				else if (strErrorHex == "C000000C")
				{
						strErrorText = "STATUS_TIMER_NOT_CANCELED";
				}
//ORIGINAL LINE: case "C000000D":
				else if (strErrorHex == "C000000D")
				{
						strErrorText = "STATUS_INVALID_PARAMETER";
				}
//ORIGINAL LINE: case "C000000E":
				else if (strErrorHex == "C000000E")
				{
						strErrorText = "STATUS_NO_SUCH_DEVICE";
				}
//ORIGINAL LINE: case "C000000F":
				else if (strErrorHex == "C000000F")
				{
						strErrorText = "STATUS_NO_SUCH_FILE";
				}
//ORIGINAL LINE: case "C0000010":
				else if (strErrorHex == "C0000010")
				{
						strErrorText = "STATUS_INVALID_DEVICE_REQUEST";
				}
//ORIGINAL LINE: case "C0000011":
				else if (strErrorHex == "C0000011")
				{
						strErrorText = "STATUS_END_OF_FILE";
				}
//ORIGINAL LINE: case "C0000012":
				else if (strErrorHex == "C0000012")
				{
						strErrorText = "STATUS_WRONG_VOLUME";
				}
//ORIGINAL LINE: case "C0000013":
				else if (strErrorHex == "C0000013")
				{
						strErrorText = "STATUS_NO_MEDIA_IN_DEVICE";
				}
//ORIGINAL LINE: case "C0000014":
				else if (strErrorHex == "C0000014")
				{
						strErrorText = "STATUS_UNRECOGNIZED_MEDIA";
				}
//ORIGINAL LINE: case "C0000015":
				else if (strErrorHex == "C0000015")
				{
						strErrorText = "STATUS_NONEXISTENT_SECTOR";
				}
//ORIGINAL LINE: case "C0000016":
				else if (strErrorHex == "C0000016")
				{
						strErrorText = "STATUS_MORE_PROCESSING_REQUIRED";
				}
//ORIGINAL LINE: case "C0000017":
				else if (strErrorHex == "C0000017")
				{
						strErrorText = "STATUS_NO_MEMORY";
				}
//ORIGINAL LINE: case "C0000018":
				else if (strErrorHex == "C0000018")
				{
						strErrorText = "STATUS_CONFLICTING_ADDRESSES";
				}
//ORIGINAL LINE: case "C0000019":
				else if (strErrorHex == "C0000019")
				{
						strErrorText = "STATUS_NOT_MAPPED_VIEW";
				}
//ORIGINAL LINE: case "C000001A":
				else if (strErrorHex == "C000001A")
				{
						strErrorText = "STATUS_UNABLE_TO_FREE_VM";
				}
//ORIGINAL LINE: case "C000001B":
				else if (strErrorHex == "C000001B")
				{
						strErrorText = "STATUS_UNABLE_TO_DELETE_SECTION";
				}
//ORIGINAL LINE: case "C000001C":
				else if (strErrorHex == "C000001C")
				{
						strErrorText = "STATUS_INVALID_SYSTEM_SERVICE";
				}
//ORIGINAL LINE: case "C000001D":
				else if (strErrorHex == "C000001D")
				{
						strErrorText = "STATUS_ILLEGAL_INSTRUCTION";
				}
//ORIGINAL LINE: case "C000001E":
				else if (strErrorHex == "C000001E")
				{
						strErrorText = "STATUS_INVALID_LOCK_SEQUENCE";
				}
//ORIGINAL LINE: case "C000001F":
				else if (strErrorHex == "C000001F")
				{
						strErrorText = "STATUS_INVALID_VIEW_SIZE";
				}
//ORIGINAL LINE: case "C0000020":
				else if (strErrorHex == "C0000020")
				{
						strErrorText = "STATUS_INVALID_FILE_FOR_SECTION";
				}
//ORIGINAL LINE: case "C0000021":
				else if (strErrorHex == "C0000021")
				{
						strErrorText = "STATUS_ALREADY_COMMITTED";
				}
//ORIGINAL LINE: case "C0000022":
				else if (strErrorHex == "C0000022")
				{
						strErrorText = "STATUS_ACCESS_DENIED";
				}
//ORIGINAL LINE: case "C0000023":
				else if (strErrorHex == "C0000023")
				{
						strErrorText = "STATUS_BUFFER_TOO_SMALL";
				}
//ORIGINAL LINE: case "C0000024":
				else if (strErrorHex == "C0000024")
				{
						strErrorText = "STATUS_OBJECT_TYPE_MISMATCH";
				}
//ORIGINAL LINE: case "C0000025":
				else if (strErrorHex == "C0000025")
				{
						strErrorText = "STATUS_NONCONTINUABLE_EXCEPTION";
				}
//ORIGINAL LINE: case "C0000026":
				else if (strErrorHex == "C0000026")
				{
						strErrorText = "STATUS_INVALID_DISPOSITION";
				}
//ORIGINAL LINE: case "C0000027":
				else if (strErrorHex == "C0000027")
				{
						strErrorText = "STATUS_UNWIND";
				}
//ORIGINAL LINE: case "C0000028":
				else if (strErrorHex == "C0000028")
				{
						strErrorText = "STATUS_BAD_STACK";
				}
//ORIGINAL LINE: case "C0000029":
				else if (strErrorHex == "C0000029")
				{
						strErrorText = "STATUS_INVALID_UNWIND_TARGET";
				}
//ORIGINAL LINE: case "C000002A":
				else if (strErrorHex == "C000002A")
				{
						strErrorText = "STATUS_NOT_LOCKED";
				}
//ORIGINAL LINE: case "C000002B":
				else if (strErrorHex == "C000002B")
				{
						strErrorText = "STATUS_PARITY_ERROR";
				}
//ORIGINAL LINE: case "C000002C":
				else if (strErrorHex == "C000002C")
				{
						strErrorText = "STATUS_UNABLE_TO_DECOMMIT_VM";
				}
//ORIGINAL LINE: case "C000002D":
				else if (strErrorHex == "C000002D")
				{
						strErrorText = "STATUS_NOT_COMMITTED";
				}
//ORIGINAL LINE: case "C000002E":
				else if (strErrorHex == "C000002E")
				{
						strErrorText = "STATUS_INVALID_PORT_ATTRIBUTES";
				}
//ORIGINAL LINE: case "C000002F":
				else if (strErrorHex == "C000002F")
				{
						strErrorText = "STATUS_PORT_MESSAGE_TOO_LONG";
				}
//ORIGINAL LINE: case "C0000030":
				else if (strErrorHex == "C0000030")
				{
						strErrorText = "STATUS_INVALID_PARAMETER_MIX";
				}
//ORIGINAL LINE: case "C0000031":
				else if (strErrorHex == "C0000031")
				{
						strErrorText = "STATUS_INVALID_QUOTA_LOWER";
				}
//ORIGINAL LINE: case "C0000032":
				else if (strErrorHex == "C0000032")
				{
						strErrorText = "STATUS_DISK_CORRUPT_ERROR";
				}
//ORIGINAL LINE: case "C0000033":
				else if (strErrorHex == "C0000033")
				{
						strErrorText = "STATUS_OBJECT_NAME_INVALID";
				}
//ORIGINAL LINE: case "C0000034":
				else if (strErrorHex == "C0000034")
				{
						strErrorText = "STATUS_OBJECT_NAME_NOT_FOUND";
				}
//ORIGINAL LINE: case "C0000035":
				else if (strErrorHex == "C0000035")
				{
						strErrorText = "STATUS_OBJECT_NAME_COLLISION";
				}
//ORIGINAL LINE: case "C0000037":
				else if (strErrorHex == "C0000037")
				{
						strErrorText = "STATUS_PORT_DISCONNECTED";
				}
//ORIGINAL LINE: case "C0000038":
				else if (strErrorHex == "C0000038")
				{
						strErrorText = "STATUS_DEVICE_ALREADY_ATTACHED";
				}
//ORIGINAL LINE: case "C0000039":
				else if (strErrorHex == "C0000039")
				{
						strErrorText = "STATUS_OBJECT_PATH_INVALID";
				}
//ORIGINAL LINE: case "C000003A":
				else if (strErrorHex == "C000003A")
				{
						strErrorText = "STATUS_OBJECT_PATH_NOT_FOUND";
				}
//ORIGINAL LINE: case "C000003B":
				else if (strErrorHex == "C000003B")
				{
						strErrorText = "STATUS_OBJECT_PATH_SYNTAX_BAD";
				}
//ORIGINAL LINE: case "C000003C":
				else if (strErrorHex == "C000003C")
				{
						strErrorText = "STATUS_DATA_OVERRUN";
				}
//ORIGINAL LINE: case "C000003D":
				else if (strErrorHex == "C000003D")
				{
						strErrorText = "STATUS_DATA_LATE_ERROR";
				}
//ORIGINAL LINE: case "C000003E":
				else if (strErrorHex == "C000003E")
				{
						strErrorText = "STATUS_DATA_ERROR";
				}
//ORIGINAL LINE: case "C000003F":
				else if (strErrorHex == "C000003F")
				{
						strErrorText = "STATUS_CRC_ERROR";
				}
//ORIGINAL LINE: case "C0000040":
				else if (strErrorHex == "C0000040")
				{
						strErrorText = "STATUS_SECTION_TOO_BIG";
				}
//ORIGINAL LINE: case "C0000041":
				else if (strErrorHex == "C0000041")
				{
						strErrorText = "STATUS_PORT_CONNECTION_REFUSED";
				}
//ORIGINAL LINE: case "C0000042":
				else if (strErrorHex == "C0000042")
				{
						strErrorText = "STATUS_INVALID_PORT_HANDLE";
				}
//ORIGINAL LINE: case "C0000043":
				else if (strErrorHex == "C0000043")
				{
						strErrorText = "STATUS_SHARING_VIOLATION";
				}
//ORIGINAL LINE: case "C0000044":
				else if (strErrorHex == "C0000044")
				{
						strErrorText = "STATUS_QUOTA_EXCEEDED";
				}
//ORIGINAL LINE: case "C0000045":
				else if (strErrorHex == "C0000045")
				{
						strErrorText = "STATUS_INVALID_PAGE_PROTECTION";
				}
//ORIGINAL LINE: case "C0000046":
				else if (strErrorHex == "C0000046")
				{
						strErrorText = "STATUS_MUTANT_NOT_OWNED";
				}
//ORIGINAL LINE: case "C0000047":
				else if (strErrorHex == "C0000047")
				{
						strErrorText = "STATUS_SEMAPHORE_LIMIT_EXCEEDED";
				}
//ORIGINAL LINE: case "C0000048":
				else if (strErrorHex == "C0000048")
				{
						strErrorText = "STATUS_PORT_ALREADY_SET";
				}
//ORIGINAL LINE: case "C0000049":
				else if (strErrorHex == "C0000049")
				{
						strErrorText = "STATUS_SECTION_NOT_IMAGE";
				}
//ORIGINAL LINE: case "C000004A":
				else if (strErrorHex == "C000004A")
				{
						strErrorText = "STATUS_SUSPEND_COUNT_EXCEEDED";
				}
//ORIGINAL LINE: case "C000004B":
				else if (strErrorHex == "C000004B")
				{
						strErrorText = "STATUS_THREAD_IS_TERMINATING";
				}
//ORIGINAL LINE: case "C000004C":
				else if (strErrorHex == "C000004C")
				{
						strErrorText = "STATUS_BAD_WORKING_SET_LIMIT";
				}
//ORIGINAL LINE: case "C000004D":
				else if (strErrorHex == "C000004D")
				{
						strErrorText = "STATUS_INCOMPATIBLE_FILE_MAP";
				}
//ORIGINAL LINE: case "C000004E":
				else if (strErrorHex == "C000004E")
				{
						strErrorText = "STATUS_SECTION_PROTECTION";
				}
//ORIGINAL LINE: case "C000004F":
				else if (strErrorHex == "C000004F")
				{
						strErrorText = "STATUS_EAS_NOT_SUPPORTED";
				}
//ORIGINAL LINE: case "C0000050":
				else if (strErrorHex == "C0000050")
				{
						strErrorText = "STATUS_EA_TOO_LARGE";
				}
//ORIGINAL LINE: case "C0000051":
				else if (strErrorHex == "C0000051")
				{
						strErrorText = "STATUS_NONEXISTENT_EA_ENTRY";
				}
//ORIGINAL LINE: case "C0000052":
				else if (strErrorHex == "C0000052")
				{
						strErrorText = "STATUS_NO_EAS_ON_FILE";
				}
//ORIGINAL LINE: case "C0000053":
				else if (strErrorHex == "C0000053")
				{
						strErrorText = "STATUS_EA_CORRUPT_ERROR";
				}
//ORIGINAL LINE: case "C0000054":
				else if (strErrorHex == "C0000054")
				{
						strErrorText = "STATUS_FILE_LOCK_CONFLICT";
				}
//ORIGINAL LINE: case "C0000055":
				else if (strErrorHex == "C0000055")
				{
						strErrorText = "STATUS_LOCK_NOT_GRANTED";
				}
//ORIGINAL LINE: case "C0000056":
				else if (strErrorHex == "C0000056")
				{
						strErrorText = "STATUS_DELETE_PENDING";
				}
//ORIGINAL LINE: case "C0000057":
				else if (strErrorHex == "C0000057")
				{
						strErrorText = "STATUS_CTL_FILE_NOT_SUPPORTED";
				}
//ORIGINAL LINE: case "C0000058":
				else if (strErrorHex == "C0000058")
				{
						strErrorText = "STATUS_UNKNOWN_REVISION";
				}
//ORIGINAL LINE: case "C0000059":
				else if (strErrorHex == "C0000059")
				{
						strErrorText = "STATUS_REVISION_MISMATCH";
				}
//ORIGINAL LINE: case "C000005A":
				else if (strErrorHex == "C000005A")
				{
						strErrorText = "STATUS_INVALID_OWNER";
				}
//ORIGINAL LINE: case "C000005B":
				else if (strErrorHex == "C000005B")
				{
						strErrorText = "STATUS_INVALID_PRIMARY_GROUP";
				}
//ORIGINAL LINE: case "C000005C":
				else if (strErrorHex == "C000005C")
				{
						strErrorText = "STATUS_NO_IMPERSONATION_TOKEN";
				}
//ORIGINAL LINE: case "C000005D":
				else if (strErrorHex == "C000005D")
				{
						strErrorText = "STATUS_CANT_DISABLE_MANDATORY";
				}
//ORIGINAL LINE: case "C000005E":
				else if (strErrorHex == "C000005E")
				{
						strErrorText = "STATUS_NO_LOGON_SERVERS";
				}
//ORIGINAL LINE: case "C000005F":
				else if (strErrorHex == "C000005F")
				{
						strErrorText = "STATUS_NO_SUCH_LOGON_SESSION";
				}
//ORIGINAL LINE: case "C0000060":
				else if (strErrorHex == "C0000060")
				{
						strErrorText = "STATUS_NO_SUCH_PRIVILEGE";
				}
//ORIGINAL LINE: case "C0000061":
				else if (strErrorHex == "C0000061")
				{
						strErrorText = "STATUS_PRIVILEGE_NOT_HELD";
				}
//ORIGINAL LINE: case "C0000062":
				else if (strErrorHex == "C0000062")
				{
						strErrorText = "STATUS_INVALID_ACCOUNT_NAME";
				}
//ORIGINAL LINE: case "C0000063":
				else if (strErrorHex == "C0000063")
				{
						strErrorText = "STATUS_USER_EXISTS";
				}
//ORIGINAL LINE: case "C0000064":
				else if (strErrorHex == "C0000064")
				{
						strErrorText = "STATUS_NO_SUCH_USER";
				}
//ORIGINAL LINE: case "C0000065":
				else if (strErrorHex == "C0000065")
				{
						strErrorText = "STATUS_GROUP_EXISTS";
				}
//ORIGINAL LINE: case "C0000066":
				else if (strErrorHex == "C0000066")
				{
						strErrorText = "STATUS_NO_SUCH_GROUP";
				}
//ORIGINAL LINE: case "C0000067":
				else if (strErrorHex == "C0000067")
				{
						strErrorText = "STATUS_MEMBER_IN_GROUP";
				}
//ORIGINAL LINE: case "C0000068":
				else if (strErrorHex == "C0000068")
				{
						strErrorText = "STATUS_MEMBER_NOT_IN_GROUP";
				}
//ORIGINAL LINE: case "C0000069":
				else if (strErrorHex == "C0000069")
				{
						strErrorText = "STATUS_LAST_ADMIN";
				}
//ORIGINAL LINE: case "C000006A":
				else if (strErrorHex == "C000006A")
				{
						strErrorText = "STATUS_WRONG_PASSWORD";
				}
//ORIGINAL LINE: case "C000006B":
				else if (strErrorHex == "C000006B")
				{
						strErrorText = "STATUS_ILL_FORMED_PASSWORD";
				}
//ORIGINAL LINE: case "C000006C":
				else if (strErrorHex == "C000006C")
				{
						strErrorText = "STATUS_PASSWORD_RESTRICTION";
				}
//ORIGINAL LINE: case "C000006D":
				else if (strErrorHex == "C000006D")
				{
						strErrorText = "STATUS_LOGON_FAILURE";
				}
//ORIGINAL LINE: case "C000006E":
				else if (strErrorHex == "C000006E")
				{
						strErrorText = "STATUS_ACCOUNT_RESTRICTION";
				}
//ORIGINAL LINE: case "C000006F":
				else if (strErrorHex == "C000006F")
				{
						strErrorText = "STATUS_INVALID_LOGON_HOURS";
				}
//ORIGINAL LINE: case "C0000070":
				else if (strErrorHex == "C0000070")
				{
						strErrorText = "STATUS_INVALID_WORKSTATION";
				}
//ORIGINAL LINE: case "C0000071":
				else if (strErrorHex == "C0000071")
				{
						strErrorText = "STATUS_PASSWORD_EXPIRED";
				}
//ORIGINAL LINE: case "C0000072":
				else if (strErrorHex == "C0000072")
				{
						strErrorText = "STATUS_ACCOUNT_DISABLED";
				}
//ORIGINAL LINE: case "C0000073":
				else if (strErrorHex == "C0000073")
				{
						strErrorText = "STATUS_NONE_MAPPED";
				}
//ORIGINAL LINE: case "C0000074":
				else if (strErrorHex == "C0000074")
				{
						strErrorText = "STATUS_TOO_MANY_LUIDS_REQUESTED";
				}
//ORIGINAL LINE: case "C0000075":
				else if (strErrorHex == "C0000075")
				{
						strErrorText = "STATUS_LUIDS_EXHAUSTED";
				}
//ORIGINAL LINE: case "C0000076":
				else if (strErrorHex == "C0000076")
				{
						strErrorText = "STATUS_INVALID_SUB_AUTHORITY";
				}
//ORIGINAL LINE: case "C0000077":
				else if (strErrorHex == "C0000077")
				{
						strErrorText = "STATUS_INVALID_ACL";
				}
//ORIGINAL LINE: case "C0000078":
				else if (strErrorHex == "C0000078")
				{
						strErrorText = "STATUS_INVALID_SID";
				}
//ORIGINAL LINE: case "C0000079":
				else if (strErrorHex == "C0000079")
				{
						strErrorText = "STATUS_INVALID_SECURITY_DESCR";
				}
//ORIGINAL LINE: case "C000007A":
				else if (strErrorHex == "C000007A")
				{
						strErrorText = "STATUS_PROCEDURE_NOT_FOUND";
				}
//ORIGINAL LINE: case "C000007B":
				else if (strErrorHex == "C000007B")
				{
						strErrorText = "STATUS_INVALID_IMAGE_FORMAT";
				}
//ORIGINAL LINE: case "C000007C":
				else if (strErrorHex == "C000007C")
				{
						strErrorText = "STATUS_NO_TOKEN";
				}
//ORIGINAL LINE: case "C000007D":
				else if (strErrorHex == "C000007D")
				{
						strErrorText = "STATUS_BAD_INHERITANCE_ACL";
				}
//ORIGINAL LINE: case "C000007E":
				else if (strErrorHex == "C000007E")
				{
						strErrorText = "STATUS_RANGE_NOT_LOCKED";
				}
//ORIGINAL LINE: case "C000007F":
				else if (strErrorHex == "C000007F")
				{
						strErrorText = "STATUS_DISK_FULL";
				}
//ORIGINAL LINE: case "C0000080":
				else if (strErrorHex == "C0000080")
				{
						strErrorText = "STATUS_SERVER_DISABLED";
				}
//ORIGINAL LINE: case "C0000081":
				else if (strErrorHex == "C0000081")
				{
						strErrorText = "STATUS_SERVER_NOT_DISABLED";
				}
//ORIGINAL LINE: case "C0000082":
				else if (strErrorHex == "C0000082")
				{
						strErrorText = "STATUS_TOO_MANY_GUIDS_REQUESTED";
				}
//ORIGINAL LINE: case "C0000083":
				else if (strErrorHex == "C0000083")
				{
						strErrorText = "STATUS_GUIDS_EXHAUSTED";
				}
//ORIGINAL LINE: case "C0000084":
				else if (strErrorHex == "C0000084")
				{
						strErrorText = "STATUS_INVALID_ID_AUTHORITY";
				}
//ORIGINAL LINE: case "C0000085":
				else if (strErrorHex == "C0000085")
				{
						strErrorText = "STATUS_AGENTS_EXHAUSTED";
				}
//ORIGINAL LINE: case "C0000086":
				else if (strErrorHex == "C0000086")
				{
						strErrorText = "STATUS_INVALID_VOLUME_LABEL";
				}
//ORIGINAL LINE: case "C0000087":
				else if (strErrorHex == "C0000087")
				{
						strErrorText = "STATUS_SECTION_NOT_EXTENDED";
				}
//ORIGINAL LINE: case "C0000088":
				else if (strErrorHex == "C0000088")
				{
						strErrorText = "STATUS_NOT_MAPPED_DATA";
				}
//ORIGINAL LINE: case "C0000089":
				else if (strErrorHex == "C0000089")
				{
						strErrorText = "STATUS_RESOURCE_DATA_NOT_FOUND";
				}
//ORIGINAL LINE: case "C000008A":
				else if (strErrorHex == "C000008A")
				{
						strErrorText = "STATUS_RESOURCE_TYPE_NOT_FOUND";
				}
//ORIGINAL LINE: case "C000008B":
				else if (strErrorHex == "C000008B")
				{
						strErrorText = "STATUS_RESOURCE_NAME_NOT_FOUND";
				}
//ORIGINAL LINE: case "C000008C":
				else if (strErrorHex == "C000008C")
				{
						strErrorText = "STATUS_ARRAY_BOUNDS_EXCEEDED";
				}
//ORIGINAL LINE: case "C000008D":
				else if (strErrorHex == "C000008D")
				{
						strErrorText = "STATUS_FLOAT_DENORMAL_OPERAND";
				}
//ORIGINAL LINE: case "C000008E":
				else if (strErrorHex == "C000008E")
				{
						strErrorText = "STATUS_FLOAT_DIVIDE_BY_ZERO";
				}
//ORIGINAL LINE: case "C000008F":
				else if (strErrorHex == "C000008F")
				{
						strErrorText = "STATUS_FLOAT_INEXACT_RESULT";
				}
//ORIGINAL LINE: case "C0000090":
				else if (strErrorHex == "C0000090")
				{
						strErrorText = "STATUS_FLOAT_INVALID_OPERATION";
				}
//ORIGINAL LINE: case "C0000091":
				else if (strErrorHex == "C0000091")
				{
						strErrorText = "STATUS_FLOAT_OVERFLOW";
				}
//ORIGINAL LINE: case "C0000092":
				else if (strErrorHex == "C0000092")
				{
						strErrorText = "STATUS_FLOAT_STACK_CHECK";
				}
//ORIGINAL LINE: case "C0000093":
				else if (strErrorHex == "C0000093")
				{
						strErrorText = "STATUS_FLOAT_UNDERFLOW";
				}
//ORIGINAL LINE: case "C0000094":
				else if (strErrorHex == "C0000094")
				{
						strErrorText = "STATUS_INTEGER_DIVIDE_BY_ZERO";
				}
//ORIGINAL LINE: case "C0000095":
				else if (strErrorHex == "C0000095")
				{
						strErrorText = "STATUS_INTEGER_OVERFLOW";
				}
//ORIGINAL LINE: case "C0000096":
				else if (strErrorHex == "C0000096")
				{
						strErrorText = "STATUS_PRIVILEGED_INSTRUCTION";
				}
//ORIGINAL LINE: case "C0000097":
				else if (strErrorHex == "C0000097")
				{
						strErrorText = "STATUS_TOO_MANY_PAGING_FILES";
				}
//ORIGINAL LINE: case "C0000098":
				else if (strErrorHex == "C0000098")
				{
						strErrorText = "STATUS_FILE_INVALID";
				}
//ORIGINAL LINE: case "C0000099":
				else if (strErrorHex == "C0000099")
				{
						strErrorText = "STATUS_ALLOTTED_SPACE_EXCEEDED";
				}
//ORIGINAL LINE: case "C000009A":
				else if (strErrorHex == "C000009A")
				{
						strErrorText = "STATUS_INSUFFICIENT_RESOURCES";
				}
//ORIGINAL LINE: case "C000009B":
				else if (strErrorHex == "C000009B")
				{
						strErrorText = "STATUS_DFS_EXIT_PATH_FOUND";
				}
//ORIGINAL LINE: case "C000009C":
				else if (strErrorHex == "C000009C")
				{
						strErrorText = "STATUS_DEVICE_DATA_ERROR";
				}
//ORIGINAL LINE: case "C000009D":
				else if (strErrorHex == "C000009D")
				{
						strErrorText = "STATUS_DEVICE_NOT_CONNECTED";
				}
//ORIGINAL LINE: case "C000009E":
				else if (strErrorHex == "C000009E")
				{
						strErrorText = "STATUS_DEVICE_POWER_FAILURE";
				}
//ORIGINAL LINE: case "C000009F":
				else if (strErrorHex == "C000009F")
				{
						strErrorText = "STATUS_FREE_VM_NOT_AT_BASE";
				}
//ORIGINAL LINE: case "C00000A0":
				else if (strErrorHex == "C00000A0")
				{
						strErrorText = "STATUS_MEMORY_NOT_ALLOCATED";
				}
//ORIGINAL LINE: case "C00000A1":
				else if (strErrorHex == "C00000A1")
				{
						strErrorText = "STATUS_WORKING_SET_QUOTA";
				}
//ORIGINAL LINE: case "C00000A2":
				else if (strErrorHex == "C00000A2")
				{
						strErrorText = "STATUS_MEDIA_WRITE_PROTECTED";
				}
//ORIGINAL LINE: case "C00000A3":
				else if (strErrorHex == "C00000A3")
				{
						strErrorText = "STATUS_DEVICE_NOT_READY";
				}
//ORIGINAL LINE: case "C00000A4":
				else if (strErrorHex == "C00000A4")
				{
						strErrorText = "STATUS_INVALID_GROUP_ATTRIBUTES";
				}
//ORIGINAL LINE: case "C00000A5":
				else if (strErrorHex == "C00000A5")
				{
						strErrorText = "STATUS_BAD_IMPERSONATION_LEVEL";
				}
//ORIGINAL LINE: case "C00000A6":
				else if (strErrorHex == "C00000A6")
				{
						strErrorText = "STATUS_CANT_OPEN_ANONYMOUS";
				}
//ORIGINAL LINE: case "C00000A7":
				else if (strErrorHex == "C00000A7")
				{
						strErrorText = "STATUS_BAD_VALIDATION_CLASS";
				}
//ORIGINAL LINE: case "C00000A8":
				else if (strErrorHex == "C00000A8")
				{
						strErrorText = "STATUS_BAD_TOKEN_TYPE";
				}
//ORIGINAL LINE: case "C00000A9":
				else if (strErrorHex == "C00000A9")
				{
						strErrorText = "STATUS_BAD_MASTER_BOOT_RECORD";
				}
//ORIGINAL LINE: case "C00000AA":
				else if (strErrorHex == "C00000AA")
				{
						strErrorText = "STATUS_INSTRUCTION_MISALIGNMENT";
				}
//ORIGINAL LINE: case "C00000AB":
				else if (strErrorHex == "C00000AB")
				{
						strErrorText = "STATUS_INSTANCE_NOT_AVAILABLE";
				}
//ORIGINAL LINE: case "C00000AC":
				else if (strErrorHex == "C00000AC")
				{
						strErrorText = "STATUS_PIPE_NOT_AVAILABLE";
				}
//ORIGINAL LINE: case "C00000AD":
				else if (strErrorHex == "C00000AD")
				{
						strErrorText = "STATUS_INVALID_PIPE_STATE";
				}
//ORIGINAL LINE: case "C00000AE":
				else if (strErrorHex == "C00000AE")
				{
						strErrorText = "STATUS_PIPE_BUSY";
				}
//ORIGINAL LINE: case "C00000AF":
				else if (strErrorHex == "C00000AF")
				{
						strErrorText = "STATUS_ILLEGAL_FUNCTION";
				}
//ORIGINAL LINE: case "C00000B0":
				else if (strErrorHex == "C00000B0")
				{
						strErrorText = "STATUS_PIPE_DISCONNECTED";
				}
//ORIGINAL LINE: case "C00000B1":
				else if (strErrorHex == "C00000B1")
				{
						strErrorText = "STATUS_PIPE_CLOSING";
				}
//ORIGINAL LINE: case "C00000B2":
				else if (strErrorHex == "C00000B2")
				{
						strErrorText = "STATUS_PIPE_CONNECTED";
				}
//ORIGINAL LINE: case "C00000B3":
				else if (strErrorHex == "C00000B3")
				{
						strErrorText = "STATUS_PIPE_LISTENING";
				}
//ORIGINAL LINE: case "C00000B4":
				else if (strErrorHex == "C00000B4")
				{
						strErrorText = "STATUS_INVALID_READ_MODE";
				}
//ORIGINAL LINE: case "C00000B5":
				else if (strErrorHex == "C00000B5")
				{
						strErrorText = "STATUS_IO_TIMEOUT";
				}
//ORIGINAL LINE: case "C00000B6":
				else if (strErrorHex == "C00000B6")
				{
						strErrorText = "STATUS_FILE_FORCED_CLOSED";
				}
//ORIGINAL LINE: case "C00000B7":
				else if (strErrorHex == "C00000B7")
				{
						strErrorText = "STATUS_PROFILING_NOT_STARTED";
				}
//ORIGINAL LINE: case "C00000B8":
				else if (strErrorHex == "C00000B8")
				{
						strErrorText = "STATUS_PROFILING_NOT_STOPPED";
				}
//ORIGINAL LINE: case "C00000B9":
				else if (strErrorHex == "C00000B9")
				{
						strErrorText = "STATUS_COULD_NOT_INTERPRET";
				}
//ORIGINAL LINE: case "C00000BA":
				else if (strErrorHex == "C00000BA")
				{
						strErrorText = "STATUS_FILE_IS_A_DIRECTORY";
				}
//ORIGINAL LINE: case "C00000BB":
				else if (strErrorHex == "C00000BB")
				{
						strErrorText = "STATUS_NOT_SUPPORTED";
				}
//ORIGINAL LINE: case "C00000BC":
				else if (strErrorHex == "C00000BC")
				{
						strErrorText = "STATUS_REMOTE_NOT_LISTENING";
				}
//ORIGINAL LINE: case "C00000BD":
				else if (strErrorHex == "C00000BD")
				{
						strErrorText = "STATUS_DUPLICATE_NAME";
				}
//ORIGINAL LINE: case "C00000BE":
				else if (strErrorHex == "C00000BE")
				{
						strErrorText = "STATUS_BAD_NETWORK_PATH";
				}
//ORIGINAL LINE: case "C00000BF":
				else if (strErrorHex == "C00000BF")
				{
						strErrorText = "STATUS_NETWORK_BUSY";
				}
//ORIGINAL LINE: case "C00000C0":
				else if (strErrorHex == "C00000C0")
				{
						strErrorText = "STATUS_DEVICE_DOES_NOT_EXIST";
				}
//ORIGINAL LINE: case "C00000C1":
				else if (strErrorHex == "C00000C1")
				{
						strErrorText = "STATUS_TOO_MANY_COMMANDS";
				}
//ORIGINAL LINE: case "C00000C2":
				else if (strErrorHex == "C00000C2")
				{
						strErrorText = "STATUS_ADAPTER_HARDWARE_ERROR";
				}
//ORIGINAL LINE: case "C00000C3":
				else if (strErrorHex == "C00000C3")
				{
						strErrorText = "STATUS_INVALID_NETWORK_RESPONSE";
				}
//ORIGINAL LINE: case "C00000C4":
				else if (strErrorHex == "C00000C4")
				{
						strErrorText = "STATUS_UNEXPECTED_NETWORK_ERROR";
				}
//ORIGINAL LINE: case "C00000C5":
				else if (strErrorHex == "C00000C5")
				{
						strErrorText = "STATUS_BAD_REMOTE_ADAPTER";
				}
//ORIGINAL LINE: case "C00000C6":
				else if (strErrorHex == "C00000C6")
				{
						strErrorText = "STATUS_PRINT_QUEUE_FULL";
				}
//ORIGINAL LINE: case "C00000C7":
				else if (strErrorHex == "C00000C7")
				{
						strErrorText = "STATUS_NO_SPOOL_SPACE";
				}
//ORIGINAL LINE: case "C00000C8":
				else if (strErrorHex == "C00000C8")
				{
						strErrorText = "STATUS_PRINT_CANCELLED";
				}
//ORIGINAL LINE: case "C00000C9":
				else if (strErrorHex == "C00000C9")
				{
						strErrorText = "STATUS_NETWORK_NAME_DELETED";
				}
//ORIGINAL LINE: case "C00000CA":
				else if (strErrorHex == "C00000CA")
				{
						strErrorText = "STATUS_NETWORK_ACCESS_DENIED";
				}
//ORIGINAL LINE: case "C00000CB":
				else if (strErrorHex == "C00000CB")
				{
						strErrorText = "STATUS_BAD_DEVICE_TYPE";
				}
//ORIGINAL LINE: case "C00000CC":
				else if (strErrorHex == "C00000CC")
				{
						strErrorText = "STATUS_BAD_NETWORK_NAME";
				}
//ORIGINAL LINE: case "C00000CD":
				else if (strErrorHex == "C00000CD")
				{
						strErrorText = "STATUS_TOO_MANY_NAMES";
				}
//ORIGINAL LINE: case "C00000CE":
				else if (strErrorHex == "C00000CE")
				{
						strErrorText = "STATUS_TOO_MANY_SESSIONS";
				}
//ORIGINAL LINE: case "C00000CF":
				else if (strErrorHex == "C00000CF")
				{
						strErrorText = "STATUS_SHARING_PAUSED";
				}
//ORIGINAL LINE: case "C00000D0":
				else if (strErrorHex == "C00000D0")
				{
						strErrorText = "STATUS_REQUEST_NOT_ACCEPTED";
				}
//ORIGINAL LINE: case "C00000D1":
				else if (strErrorHex == "C00000D1")
				{
						strErrorText = "STATUS_REDIRECTOR_PAUSED";
				}
//ORIGINAL LINE: case "C00000D2":
				else if (strErrorHex == "C00000D2")
				{
						strErrorText = "STATUS_NET_WRITE_FAULT";
				}
//ORIGINAL LINE: case "C00000D3":
				else if (strErrorHex == "C00000D3")
				{
						strErrorText = "STATUS_PROFILING_AT_LIMIT";
				}
//ORIGINAL LINE: case "C00000D4":
				else if (strErrorHex == "C00000D4")
				{
						strErrorText = "STATUS_NOT_SAME_DEVICE";
				}
//ORIGINAL LINE: case "C00000D5":
				else if (strErrorHex == "C00000D5")
				{
						strErrorText = "STATUS_FILE_RENAMED";
				}
//ORIGINAL LINE: case "C00000D6":
				else if (strErrorHex == "C00000D6")
				{
						strErrorText = "STATUS_VIRTUAL_CIRCUIT_CLOSED";
				}
//ORIGINAL LINE: case "C00000D7":
				else if (strErrorHex == "C00000D7")
				{
						strErrorText = "STATUS_NO_SECURITY_ON_OBJECT";
				}
//ORIGINAL LINE: case "C00000D8":
				else if (strErrorHex == "C00000D8")
				{
						strErrorText = "STATUS_CANT_WAIT";
				}
//ORIGINAL LINE: case "C00000D9":
				else if (strErrorHex == "C00000D9")
				{
						strErrorText = "STATUS_PIPE_EMPTY";
				}
//ORIGINAL LINE: case "C00000DA":
				else if (strErrorHex == "C00000DA")
				{
						strErrorText = "STATUS_CANT_ACCESS_DOMAIN_INFO";
				}
//ORIGINAL LINE: case "C00000DB":
				else if (strErrorHex == "C00000DB")
				{
						strErrorText = "STATUS_CANT_TERMINATE_SELF";
				}
//ORIGINAL LINE: case "C00000DC":
				else if (strErrorHex == "C00000DC")
				{
						strErrorText = "STATUS_INVALID_SERVER_STATE";
				}
//ORIGINAL LINE: case "C00000DD":
				else if (strErrorHex == "C00000DD")
				{
						strErrorText = "STATUS_INVALID_DOMAIN_STATE";
				}
//ORIGINAL LINE: case "C00000DE":
				else if (strErrorHex == "C00000DE")
				{
						strErrorText = "STATUS_INVALID_DOMAIN_ROLE";
				}
//ORIGINAL LINE: case "C00000DF":
				else if (strErrorHex == "C00000DF")
				{
						strErrorText = "STATUS_NO_SUCH_DOMAIN";
				}
//ORIGINAL LINE: case "C00000E0":
				else if (strErrorHex == "C00000E0")
				{
						strErrorText = "STATUS_DOMAIN_EXISTS";
				}
//ORIGINAL LINE: case "C00000E1":
				else if (strErrorHex == "C00000E1")
				{
						strErrorText = "STATUS_DOMAIN_LIMIT_EXCEEDED";
				}
//ORIGINAL LINE: case "C00000E2":
				else if (strErrorHex == "C00000E2")
				{
						strErrorText = "STATUS_OPLOCK_NOT_GRANTED";
				}
//ORIGINAL LINE: case "C00000E3":
				else if (strErrorHex == "C00000E3")
				{
						strErrorText = "STATUS_INVALID_OPLOCK_PROTOCOL";
				}
//ORIGINAL LINE: case "C00000E4":
				else if (strErrorHex == "C00000E4")
				{
						strErrorText = "STATUS_INTERNAL_DB_CORRUPTION";
				}
//ORIGINAL LINE: case "C00000E5":
				else if (strErrorHex == "C00000E5")
				{
						strErrorText = "STATUS_INTERNAL_ERROR";
				}
//ORIGINAL LINE: case "C00000E6":
				else if (strErrorHex == "C00000E6")
				{
						strErrorText = "STATUS_GENERIC_NOT_MAPPED";
				}
//ORIGINAL LINE: case "C00000E7":
				else if (strErrorHex == "C00000E7")
				{
						strErrorText = "STATUS_BAD_DESCRIPTOR_FORMAT";
				}
//ORIGINAL LINE: case "C00000E8":
				else if (strErrorHex == "C00000E8")
				{
						strErrorText = "STATUS_INVALID_USER_BUFFER";
				}
//ORIGINAL LINE: case "C00000E9":
				else if (strErrorHex == "C00000E9")
				{
						strErrorText = "STATUS_UNEXPECTED_IO_ERROR";
				}
//ORIGINAL LINE: case "C00000EA":
				else if (strErrorHex == "C00000EA")
				{
						strErrorText = "STATUS_UNEXPECTED_MM_CREATE_ERR";
				}
//ORIGINAL LINE: case "C00000EB":
				else if (strErrorHex == "C00000EB")
				{
						strErrorText = "STATUS_UNEXPECTED_MM_MAP_ERROR";
				}
//ORIGINAL LINE: case "C00000EC":
				else if (strErrorHex == "C00000EC")
				{
						strErrorText = "STATUS_UNEXPECTED_MM_EXTEND_ERR";
				}
//ORIGINAL LINE: case "C00000ED":
				else if (strErrorHex == "C00000ED")
				{
						strErrorText = "STATUS_NOT_LOGON_PROCESS";
				}
//ORIGINAL LINE: case "C00000EE":
				else if (strErrorHex == "C00000EE")
				{
						strErrorText = "STATUS_LOGON_SESSION_EXISTS";
				}
//ORIGINAL LINE: case "C00000EF":
				else if (strErrorHex == "C00000EF")
				{
						strErrorText = "STATUS_INVALID_PARAMETER_1";
				}
//ORIGINAL LINE: case "C00000F0":
				else if (strErrorHex == "C00000F0")
				{
						strErrorText = "STATUS_INVALID_PARAMETER_2";
				}
//ORIGINAL LINE: case "C00000F1":
				else if (strErrorHex == "C00000F1")
				{
						strErrorText = "STATUS_INVALID_PARAMETER_3";
				}
//ORIGINAL LINE: case "C00000F2":
				else if (strErrorHex == "C00000F2")
				{
						strErrorText = "STATUS_INVALID_PARAMETER_4";
				}
//ORIGINAL LINE: case "C00000F3":
				else if (strErrorHex == "C00000F3")
				{
						strErrorText = "STATUS_INVALID_PARAMETER_5";
				}
//ORIGINAL LINE: case "C00000F4":
				else if (strErrorHex == "C00000F4")
				{
						strErrorText = "STATUS_INVALID_PARAMETER_6";
				}
//ORIGINAL LINE: case "C00000F5":
				else if (strErrorHex == "C00000F5")
				{
						strErrorText = "STATUS_INVALID_PARAMETER_7";
				}
//ORIGINAL LINE: case "C00000F6":
				else if (strErrorHex == "C00000F6")
				{
						strErrorText = "STATUS_INVALID_PARAMETER_8";
				}
//ORIGINAL LINE: case "C00000F7":
				else if (strErrorHex == "C00000F7")
				{
						strErrorText = "STATUS_INVALID_PARAMETER_9";
				}
//ORIGINAL LINE: case "C00000F8":
				else if (strErrorHex == "C00000F8")
				{
						strErrorText = "STATUS_INVALID_PARAMETER_10";
				}
//ORIGINAL LINE: case "C00000F9":
				else if (strErrorHex == "C00000F9")
				{
						strErrorText = "STATUS_INVALID_PARAMETER_11";
				}
//ORIGINAL LINE: case "C00000FA":
				else if (strErrorHex == "C00000FA")
				{
						strErrorText = "STATUS_INVALID_PARAMETER_12";
				}
//ORIGINAL LINE: case "C00000FB":
				else if (strErrorHex == "C00000FB")
				{
						strErrorText = "STATUS_REDIRECTOR_NOT_STARTED";
				}
//ORIGINAL LINE: case "C00000FC":
				else if (strErrorHex == "C00000FC")
				{
						strErrorText = "STATUS_REDIRECTOR_STARTED";
				}
//ORIGINAL LINE: case "C00000FD":
				else if (strErrorHex == "C00000FD")
				{
						strErrorText = "STATUS_STACK_OVERFLOW";
				}
//ORIGINAL LINE: case "C00000FE":
				else if (strErrorHex == "C00000FE")
				{
						strErrorText = "STATUS_NO_SUCH_PACKAGE";
				}
//ORIGINAL LINE: case "C00000FF":
				else if (strErrorHex == "C00000FF")
				{
						strErrorText = "STATUS_BAD_FUNCTION_TABLE";
				}
//ORIGINAL LINE: case "C0000100":
				else if (strErrorHex == "C0000100")
				{
						strErrorText = "STATUS_VARIABLE_NOT_FOUND";
				}
//ORIGINAL LINE: case "C0000101":
				else if (strErrorHex == "C0000101")
				{
						strErrorText = "STATUS_DIRECTORY_NOT_EMPTY";
				}
//ORIGINAL LINE: case "C0000102":
				else if (strErrorHex == "C0000102")
				{
						strErrorText = "STATUS_FILE_CORRUPT_ERROR";
				}
//ORIGINAL LINE: case "C0000103":
				else if (strErrorHex == "C0000103")
				{
						strErrorText = "STATUS_NOT_A_DIRECTORY";
				}
//ORIGINAL LINE: case "C0000104":
				else if (strErrorHex == "C0000104")
				{
						strErrorText = "STATUS_BAD_LOGON_SESSION_STATE";
				}
//ORIGINAL LINE: case "C0000105":
				else if (strErrorHex == "C0000105")
				{
						strErrorText = "STATUS_LOGON_SESSION_COLLISION";
				}
//ORIGINAL LINE: case "C0000106":
				else if (strErrorHex == "C0000106")
				{
						strErrorText = "STATUS_NAME_TOO_LONG";
				}
//ORIGINAL LINE: case "C0000107":
				else if (strErrorHex == "C0000107")
				{
						strErrorText = "STATUS_FILES_OPEN";
				}
//ORIGINAL LINE: case "C0000108":
				else if (strErrorHex == "C0000108")
				{
						strErrorText = "STATUS_CONNECTION_IN_USE";
				}
//ORIGINAL LINE: case "C0000109":
				else if (strErrorHex == "C0000109")
				{
						strErrorText = "STATUS_MESSAGE_NOT_FOUND";
				}
//ORIGINAL LINE: case "C000010A":
				else if (strErrorHex == "C000010A")
				{
						strErrorText = "STATUS_PROCESS_IS_TERMINATING";
				}
//ORIGINAL LINE: case "C000010B":
				else if (strErrorHex == "C000010B")
				{
						strErrorText = "STATUS_INVALID_LOGON_TYPE";
				}
//ORIGINAL LINE: case "C000010C":
				else if (strErrorHex == "C000010C")
				{
						strErrorText = "STATUS_NO_GUID_TRANSLATION";
				}
//ORIGINAL LINE: case "C000010D":
				else if (strErrorHex == "C000010D")
				{
						strErrorText = "STATUS_CANNOT_IMPERSONATE";
				}
//ORIGINAL LINE: case "C000010E":
				else if (strErrorHex == "C000010E")
				{
						strErrorText = "STATUS_IMAGE_ALREADY_LOADED";
				}
//ORIGINAL LINE: case "C000010F":
				else if (strErrorHex == "C000010F")
				{
						strErrorText = "STATUS_ABIOS_NOT_PRESENT";
				}
//ORIGINAL LINE: case "C0000110":
				else if (strErrorHex == "C0000110")
				{
						strErrorText = "STATUS_ABIOS_LID_NOT_EXIST";
				}
//ORIGINAL LINE: case "C0000111":
				else if (strErrorHex == "C0000111")
				{
						strErrorText = "STATUS_ABIOS_LID_ALREADY_OWNED";
				}
//ORIGINAL LINE: case "C0000112":
				else if (strErrorHex == "C0000112")
				{
						strErrorText = "STATUS_ABIOS_NOT_LID_OWNER";
				}
//ORIGINAL LINE: case "C0000113":
				else if (strErrorHex == "C0000113")
				{
						strErrorText = "STATUS_ABIOS_INVALID_COMMAND";
				}
//ORIGINAL LINE: case "C0000114":
				else if (strErrorHex == "C0000114")
				{
						strErrorText = "STATUS_ABIOS_INVALID_LID";
				}
//ORIGINAL LINE: case "C0000115":
				else if (strErrorHex == "C0000115")
				{
						strErrorText = "STATUS_ABIOS_SELECTOR_NOT_AVAILABLE";
				}
//ORIGINAL LINE: case "C0000116":
				else if (strErrorHex == "C0000116")
				{
						strErrorText = "STATUS_ABIOS_INVALID_SELECTOR";
				}
//ORIGINAL LINE: case "C0000117":
				else if (strErrorHex == "C0000117")
				{
						strErrorText = "STATUS_NO_LDT";
				}
//ORIGINAL LINE: case "C0000118":
				else if (strErrorHex == "C0000118")
				{
						strErrorText = "STATUS_INVALID_LDT_SIZE";
				}
//ORIGINAL LINE: case "C0000119":
				else if (strErrorHex == "C0000119")
				{
						strErrorText = "STATUS_INVALID_LDT_OFFSET";
				}
//ORIGINAL LINE: case "C000011A":
				else if (strErrorHex == "C000011A")
				{
						strErrorText = "STATUS_INVALID_LDT_DESCRIPTOR";
				}
//ORIGINAL LINE: case "C000011B":
				else if (strErrorHex == "C000011B")
				{
						strErrorText = "STATUS_INVALID_IMAGE_NE_FORMAT";
				}
//ORIGINAL LINE: case "C000011C":
				else if (strErrorHex == "C000011C")
				{
						strErrorText = "STATUS_RXACT_INVALID_STATE";
				}
//ORIGINAL LINE: case "C000011D":
				else if (strErrorHex == "C000011D")
				{
						strErrorText = "STATUS_RXACT_COMMIT_FAILURE";
				}
//ORIGINAL LINE: case "C000011E":
				else if (strErrorHex == "C000011E")
				{
						strErrorText = "STATUS_MAPPED_FILE_SIZE_ZERO";
				}
//ORIGINAL LINE: case "C000011F":
				else if (strErrorHex == "C000011F")
				{
						strErrorText = "STATUS_TOO_MANY_OPENED_FILES";
				}
//ORIGINAL LINE: case "C0000120":
				else if (strErrorHex == "C0000120")
				{
						strErrorText = "STATUS_CANCELLED";
				}
//ORIGINAL LINE: case "C0000121":
				else if (strErrorHex == "C0000121")
				{
						strErrorText = "STATUS_CANNOT_DELETE";
				}
//ORIGINAL LINE: case "C0000122":
				else if (strErrorHex == "C0000122")
				{
						strErrorText = "STATUS_INVALID_COMPUTER_NAME";
				}
//ORIGINAL LINE: case "C0000123":
				else if (strErrorHex == "C0000123")
				{
						strErrorText = "STATUS_FILE_DELETED";
				}
//ORIGINAL LINE: case "C0000124":
				else if (strErrorHex == "C0000124")
				{
						strErrorText = "STATUS_SPECIAL_ACCOUNT";
				}
//ORIGINAL LINE: case "C0000125":
				else if (strErrorHex == "C0000125")
				{
						strErrorText = "STATUS_SPECIAL_GROUP";
				}
//ORIGINAL LINE: case "C0000126":
				else if (strErrorHex == "C0000126")
				{
						strErrorText = "STATUS_SPECIAL_USER";
				}
//ORIGINAL LINE: case "C0000127":
				else if (strErrorHex == "C0000127")
				{
						strErrorText = "STATUS_MEMBERS_PRIMARY_GROUP";
				}
//ORIGINAL LINE: case "C0000128":
				else if (strErrorHex == "C0000128")
				{
						strErrorText = "STATUS_FILE_CLOSED";
				}
//ORIGINAL LINE: case "C0000129":
				else if (strErrorHex == "C0000129")
				{
						strErrorText = "STATUS_TOO_MANY_THREADS";
				}
//ORIGINAL LINE: case "C000012A":
				else if (strErrorHex == "C000012A")
				{
						strErrorText = "STATUS_THREAD_NOT_IN_PROCESS";
				}
//ORIGINAL LINE: case "C000012B":
				else if (strErrorHex == "C000012B")
				{
						strErrorText = "STATUS_TOKEN_ALREADY_IN_USE";
				}
//ORIGINAL LINE: case "C000012C":
				else if (strErrorHex == "C000012C")
				{
						strErrorText = "STATUS_PAGEFILE_QUOTA_EXCEEDED";
				}
//ORIGINAL LINE: case "C000012D":
				else if (strErrorHex == "C000012D")
				{
						strErrorText = "STATUS_COMMITMENT_LIMIT";
				}
//ORIGINAL LINE: case "C000012E":
				else if (strErrorHex == "C000012E")
				{
						strErrorText = "STATUS_INVALID_IMAGE_LE_FORMAT";
				}
//ORIGINAL LINE: case "C000012F":
				else if (strErrorHex == "C000012F")
				{
						strErrorText = "STATUS_INVALID_IMAGE_NOT_MZ";
				}
//ORIGINAL LINE: case "C0000130":
				else if (strErrorHex == "C0000130")
				{
						strErrorText = "STATUS_INVALID_IMAGE_PROTECT";
				}
//ORIGINAL LINE: case "C0000131":
				else if (strErrorHex == "C0000131")
				{
						strErrorText = "STATUS_INVALID_IMAGE_WIN_16";
				}
//ORIGINAL LINE: case "C0000132":
				else if (strErrorHex == "C0000132")
				{
						strErrorText = "STATUS_LOGON_SERVER_CONFLICT";
				}
//ORIGINAL LINE: case "C0000133":
				else if (strErrorHex == "C0000133")
				{
						strErrorText = "STATUS_TIME_DIFFERENCE_AT_DC";
				}
//ORIGINAL LINE: case "C0000134":
				else if (strErrorHex == "C0000134")
				{
						strErrorText = "STATUS_SYNCHRONIZATION_REQUIRED";
				}
//ORIGINAL LINE: case "C0000135":
				else if (strErrorHex == "C0000135")
				{
						strErrorText = "STATUS_DLL_NOT_FOUND";
				}
//ORIGINAL LINE: case "C0000136":
				else if (strErrorHex == "C0000136")
				{
						strErrorText = "STATUS_OPEN_FAILED";
				}
//ORIGINAL LINE: case "C0000137":
				else if (strErrorHex == "C0000137")
				{
						strErrorText = "STATUS_IO_PRIVILEGE_FAILED";
				}
//ORIGINAL LINE: case "C0000138":
				else if (strErrorHex == "C0000138")
				{
						strErrorText = "STATUS_ORDINAL_NOT_FOUND";
				}
//ORIGINAL LINE: case "C0000139":
				else if (strErrorHex == "C0000139")
				{
						strErrorText = "STATUS_ENTRYPOINT_NOT_FOUND";
				}
//ORIGINAL LINE: case "C000013A":
				else if (strErrorHex == "C000013A")
				{
						strErrorText = "STATUS_CONTROL_C_EXIT";
				}
//ORIGINAL LINE: case "C000013B":
				else if (strErrorHex == "C000013B")
				{
						strErrorText = "STATUS_LOCAL_DISCONNECT";
				}
//ORIGINAL LINE: case "C000013C":
				else if (strErrorHex == "C000013C")
				{
						strErrorText = "STATUS_REMOTE_DISCONNECT";
				}
//ORIGINAL LINE: case "C000013D":
				else if (strErrorHex == "C000013D")
				{
						strErrorText = "STATUS_REMOTE_RESOURCES";
				}
//ORIGINAL LINE: case "C000013E":
				else if (strErrorHex == "C000013E")
				{
						strErrorText = "STATUS_LINK_FAILED";
				}
//ORIGINAL LINE: case "C000013F":
				else if (strErrorHex == "C000013F")
				{
						strErrorText = "STATUS_LINK_TIMEOUT";
				}
//ORIGINAL LINE: case "C0000140":
				else if (strErrorHex == "C0000140")
				{
						strErrorText = "STATUS_INVALID_CONNECTION";
				}
//ORIGINAL LINE: case "C0000141":
				else if (strErrorHex == "C0000141")
				{
						strErrorText = "STATUS_INVALID_ADDRESS";
				}
//ORIGINAL LINE: case "C0000142":
				else if (strErrorHex == "C0000142")
				{
						strErrorText = "STATUS_DLL_INIT_FAILED";
				}
//ORIGINAL LINE: case "C0000143":
				else if (strErrorHex == "C0000143")
				{
						strErrorText = "STATUS_MISSING_SYSTEMFILE";
				}
//ORIGINAL LINE: case "C0000144":
				else if (strErrorHex == "C0000144")
				{
						strErrorText = "STATUS_UNHANDLED_EXCEPTION";
				}
//ORIGINAL LINE: case "C0000145":
				else if (strErrorHex == "C0000145")
				{
						strErrorText = "STATUS_APP_INIT_FAILURE";
				}
//ORIGINAL LINE: case "C0000146":
				else if (strErrorHex == "C0000146")
				{
						strErrorText = "STATUS_PAGEFILE_CREATE_FAILED";
				}
//ORIGINAL LINE: case "C0000147":
				else if (strErrorHex == "C0000147")
				{
						strErrorText = "STATUS_NO_PAGEFILE";
				}
//ORIGINAL LINE: case "C0000148":
				else if (strErrorHex == "C0000148")
				{
						strErrorText = "STATUS_INVALID_LEVEL";
				}
//ORIGINAL LINE: case "C0000149":
				else if (strErrorHex == "C0000149")
				{
						strErrorText = "STATUS_WRONG_PASSWORD_CORE";
				}
//ORIGINAL LINE: case "C000014A":
				else if (strErrorHex == "C000014A")
				{
						strErrorText = "STATUS_ILLEGAL_FLOAT_CONTEXT";
				}
//ORIGINAL LINE: case "C000014B":
				else if (strErrorHex == "C000014B")
				{
						strErrorText = "STATUS_PIPE_BROKEN";
				}
//ORIGINAL LINE: case "C000014C":
				else if (strErrorHex == "C000014C")
				{
						strErrorText = "STATUS_REGISTRY_CORRUPT";
				}
//ORIGINAL LINE: case "C000014D":
				else if (strErrorHex == "C000014D")
				{
						strErrorText = "STATUS_REGISTRY_IO_FAILED";
				}
//ORIGINAL LINE: case "C000014E":
				else if (strErrorHex == "C000014E")
				{
						strErrorText = "STATUS_NO_EVENT_PAIR";
				}
//ORIGINAL LINE: case "C000014F":
				else if (strErrorHex == "C000014F")
				{
						strErrorText = "STATUS_UNRECOGNIZED_VOLUME";
				}
//ORIGINAL LINE: case "C0000150":
				else if (strErrorHex == "C0000150")
				{
						strErrorText = "STATUS_SERIAL_NO_DEVICE_INITED";
				}
//ORIGINAL LINE: case "C0000151":
				else if (strErrorHex == "C0000151")
				{
						strErrorText = "STATUS_NO_SUCH_ALIAS";
				}
//ORIGINAL LINE: case "C0000152":
				else if (strErrorHex == "C0000152")
				{
						strErrorText = "STATUS_MEMBER_NOT_IN_ALIAS";
				}
//ORIGINAL LINE: case "C0000153":
				else if (strErrorHex == "C0000153")
				{
						strErrorText = "STATUS_MEMBER_IN_ALIAS";
				}
//ORIGINAL LINE: case "C0000154":
				else if (strErrorHex == "C0000154")
				{
						strErrorText = "STATUS_ALIAS_EXISTS";
				}
//ORIGINAL LINE: case "C0000155":
				else if (strErrorHex == "C0000155")
				{
						strErrorText = "STATUS_LOGON_NOT_GRANTED";
				}
//ORIGINAL LINE: case "C0000156":
				else if (strErrorHex == "C0000156")
				{
						strErrorText = "STATUS_TOO_MANY_SECRETS";
				}
//ORIGINAL LINE: case "C0000157":
				else if (strErrorHex == "C0000157")
				{
						strErrorText = "STATUS_SECRET_TOO_LONG";
				}
//ORIGINAL LINE: case "C0000158":
				else if (strErrorHex == "C0000158")
				{
						strErrorText = "STATUS_INTERNAL_DB_ERROR";
				}
//ORIGINAL LINE: case "C0000159":
				else if (strErrorHex == "C0000159")
				{
						strErrorText = "STATUS_FULLSCREEN_MODE";
				}
//ORIGINAL LINE: case "C000015A":
				else if (strErrorHex == "C000015A")
				{
						strErrorText = "STATUS_TOO_MANY_CONTEXT_IDS";
				}
//ORIGINAL LINE: case "C000015B":
				else if (strErrorHex == "C000015B")
				{
						strErrorText = "STATUS_LOGON_TYPE_NOT_GRANTED";
				}
//ORIGINAL LINE: case "C000015C":
				else if (strErrorHex == "C000015C")
				{
						strErrorText = "STATUS_NOT_REGISTRY_FILE";
				}
//ORIGINAL LINE: case "C000015D":
				else if (strErrorHex == "C000015D")
				{
						strErrorText = "STATUS_NT_CROSS_ENCRYPTION_REQUIRED";
				}
//ORIGINAL LINE: case "C000015E":
				else if (strErrorHex == "C000015E")
				{
						strErrorText = "STATUS_DOMAIN_CTRLR_CONFIG_ERROR";
				}
//ORIGINAL LINE: case "C000015F":
				else if (strErrorHex == "C000015F")
				{
						strErrorText = "STATUS_FT_MISSING_MEMBER";
				}
//ORIGINAL LINE: case "C0000160":
				else if (strErrorHex == "C0000160")
				{
						strErrorText = "STATUS_ILL_FORMED_SERVICE_ENTRY";
				}
//ORIGINAL LINE: case "C0000161":
				else if (strErrorHex == "C0000161")
				{
						strErrorText = "STATUS_ILLEGAL_CHARACTER";
				}
//ORIGINAL LINE: case "C0000162":
				else if (strErrorHex == "C0000162")
				{
						strErrorText = "STATUS_UNMAPPABLE_CHARACTER";
				}
//ORIGINAL LINE: case "C0000163":
				else if (strErrorHex == "C0000163")
				{
						strErrorText = "STATUS_UNDEFINED_CHARACTER";
				}
//ORIGINAL LINE: case "C0000164":
				else if (strErrorHex == "C0000164")
				{
						strErrorText = "STATUS_FLOPPY_VOLUME";
				}
//ORIGINAL LINE: case "C0000165":
				else if (strErrorHex == "C0000165")
				{
						strErrorText = "STATUS_FLOPPY_ID_MARK_NOT_FOUND";
				}
//ORIGINAL LINE: case "C0000166":
				else if (strErrorHex == "C0000166")
				{
						strErrorText = "STATUS_FLOPPY_WRONG_CYLINDER";
				}
//ORIGINAL LINE: case "C0000167":
				else if (strErrorHex == "C0000167")
				{
						strErrorText = "STATUS_FLOPPY_UNKNOWN_ERROR";
				}
//ORIGINAL LINE: case "C0000168":
				else if (strErrorHex == "C0000168")
				{
						strErrorText = "STATUS_FLOPPY_BAD_REGISTERS";
				}
//ORIGINAL LINE: case "C0000169":
				else if (strErrorHex == "C0000169")
				{
						strErrorText = "STATUS_DISK_RECALIBRATE_FAILED";
				}
//ORIGINAL LINE: case "C000016A":
				else if (strErrorHex == "C000016A")
				{
						strErrorText = "STATUS_DISK_OPERATION_FAILED";
				}
//ORIGINAL LINE: case "C000016B":
				else if (strErrorHex == "C000016B")
				{
						strErrorText = "STATUS_DISK_RESET_FAILED";
				}
//ORIGINAL LINE: case "C000016C":
				else if (strErrorHex == "C000016C")
				{
						strErrorText = "STATUS_SHARED_IRQ_BUSY";
				}
//ORIGINAL LINE: case "C000016D":
				else if (strErrorHex == "C000016D")
				{
						strErrorText = "STATUS_FT_ORPHANING";
				}
//ORIGINAL LINE: case "C000016E":
				else if (strErrorHex == "C000016E")
				{
						strErrorText = "STATUS_BIOS_FAILED_TO_CONNECT_INTERRUPT";
				}
//ORIGINAL LINE: case "C0000172":
				else if (strErrorHex == "C0000172")
				{
						strErrorText = "STATUS_PARTITION_FAILURE";
				}
//ORIGINAL LINE: case "C0000173":
				else if (strErrorHex == "C0000173")
				{
						strErrorText = "STATUS_INVALID_BLOCK_LENGTH";
				}
//ORIGINAL LINE: case "C0000174":
				else if (strErrorHex == "C0000174")
				{
						strErrorText = "STATUS_DEVICE_NOT_PARTITIONED";
				}
//ORIGINAL LINE: case "C0000175":
				else if (strErrorHex == "C0000175")
				{
						strErrorText = "STATUS_UNABLE_TO_LOCK_MEDIA";
				}
//ORIGINAL LINE: case "C0000176":
				else if (strErrorHex == "C0000176")
				{
						strErrorText = "STATUS_UNABLE_TO_UNLOAD_MEDIA";
				}
//ORIGINAL LINE: case "C0000177":
				else if (strErrorHex == "C0000177")
				{
						strErrorText = "STATUS_EOM_OVERFLOW";
				}
//ORIGINAL LINE: case "C0000178":
				else if (strErrorHex == "C0000178")
				{
						strErrorText = "STATUS_NO_MEDIA";
				}
//ORIGINAL LINE: case "C000017A":
				else if (strErrorHex == "C000017A")
				{
						strErrorText = "STATUS_NO_SUCH_MEMBER";
				}
//ORIGINAL LINE: case "C000017B":
				else if (strErrorHex == "C000017B")
				{
						strErrorText = "STATUS_INVALID_MEMBER";
				}
//ORIGINAL LINE: case "C000017C":
				else if (strErrorHex == "C000017C")
				{
						strErrorText = "STATUS_KEY_DELETED";
				}
//ORIGINAL LINE: case "C000017D":
				else if (strErrorHex == "C000017D")
				{
						strErrorText = "STATUS_NO_LOG_SPACE";
				}
//ORIGINAL LINE: case "C000017E":
				else if (strErrorHex == "C000017E")
				{
						strErrorText = "STATUS_TOO_MANY_SIDS";
				}
//ORIGINAL LINE: case "C000017F":
				else if (strErrorHex == "C000017F")
				{
						strErrorText = "STATUS_LM_CROSS_ENCRYPTION_REQUIRED";
				}
//ORIGINAL LINE: case "C0000180":
				else if (strErrorHex == "C0000180")
				{
						strErrorText = "STATUS_KEY_HAS_CHILDREN";
				}
//ORIGINAL LINE: case "C0000181":
				else if (strErrorHex == "C0000181")
				{
						strErrorText = "STATUS_CHILD_MUST_BE_VOLATILE";
				}
//ORIGINAL LINE: case "C0000182":
				else if (strErrorHex == "C0000182")
				{
						strErrorText = "STATUS_DEVICE_CONFIGURATION_ERROR";
				}
//ORIGINAL LINE: case "C0000183":
				else if (strErrorHex == "C0000183")
				{
						strErrorText = "STATUS_DRIVER_INTERNAL_ERROR";
				}
//ORIGINAL LINE: case "C0000184":
				else if (strErrorHex == "C0000184")
				{
						strErrorText = "STATUS_INVALID_DEVICE_STATE";
				}
//ORIGINAL LINE: case "C0000185":
				else if (strErrorHex == "C0000185")
				{
						strErrorText = "STATUS_IO_DEVICE_ERROR";
				}
//ORIGINAL LINE: case "C0000186":
				else if (strErrorHex == "C0000186")
				{
						strErrorText = "STATUS_DEVICE_PROTOCOL_ERROR";
				}
//ORIGINAL LINE: case "C0000187":
				else if (strErrorHex == "C0000187")
				{
						strErrorText = "STATUS_BACKUP_CONTROLLER";
				}
//ORIGINAL LINE: case "C0000188":
				else if (strErrorHex == "C0000188")
				{
						strErrorText = "STATUS_LOG_FILE_FULL";
				}
//ORIGINAL LINE: case "C0000189":
				else if (strErrorHex == "C0000189")
				{
						strErrorText = "STATUS_TOO_LATE";
				}
//ORIGINAL LINE: case "C000018A":
				else if (strErrorHex == "C000018A")
				{
						strErrorText = "STATUS_NO_TRUST_LSA_SECRET";
				}
//ORIGINAL LINE: case "C000018B":
				else if (strErrorHex == "C000018B")
				{
						strErrorText = "STATUS_NO_TRUST_SAM_ACCOUNT";
				}
//ORIGINAL LINE: case "C000018C":
				else if (strErrorHex == "C000018C")
				{
						strErrorText = "STATUS_TRUSTED_DOMAIN_FAILURE";
				}
//ORIGINAL LINE: case "C000018D":
				else if (strErrorHex == "C000018D")
				{
						strErrorText = "STATUS_TRUSTED_RELATIONSHIP_FAILURE";
				}
//ORIGINAL LINE: case "C000018E":
				else if (strErrorHex == "C000018E")
				{
						strErrorText = "STATUS_EVENTLOG_FILE_CORRUPT";
				}
//ORIGINAL LINE: case "C000018F":
				else if (strErrorHex == "C000018F")
				{
						strErrorText = "STATUS_EVENTLOG_CANT_START";
				}
//ORIGINAL LINE: case "C0000190":
				else if (strErrorHex == "C0000190")
				{
						strErrorText = "STATUS_TRUST_FAILURE";
				}
//ORIGINAL LINE: case "C0000191":
				else if (strErrorHex == "C0000191")
				{
						strErrorText = "STATUS_MUTANT_LIMIT_EXCEEDED";
				}
//ORIGINAL LINE: case "C0000192":
				else if (strErrorHex == "C0000192")
				{
						strErrorText = "STATUS_NETLOGON_NOT_STARTED";
				}
//ORIGINAL LINE: case "C0000193":
				else if (strErrorHex == "C0000193")
				{
						strErrorText = "STATUS_ACCOUNT_EXPIRED";
				}
//ORIGINAL LINE: case "C0000194":
				else if (strErrorHex == "C0000194")
				{
						strErrorText = "STATUS_POSSIBLE_DEADLOCK";
				}
//ORIGINAL LINE: case "C0000195":
				else if (strErrorHex == "C0000195")
				{
						strErrorText = "STATUS_NETWORK_CREDENTIAL_CONFLICT";
				}
//ORIGINAL LINE: case "C0000196":
				else if (strErrorHex == "C0000196")
				{
						strErrorText = "STATUS_REMOTE_SESSION_LIMIT";
				}
//ORIGINAL LINE: case "C0000197":
				else if (strErrorHex == "C0000197")
				{
						strErrorText = "STATUS_EVENTLOG_FILE_CHANGED";
				}
//ORIGINAL LINE: case "C0000198":
				else if (strErrorHex == "C0000198")
				{
						strErrorText = "STATUS_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT";
				}
//ORIGINAL LINE: case "C0000199":
				else if (strErrorHex == "C0000199")
				{
						strErrorText = "STATUS_NOLOGON_WORKSTATION_TRUST_ACCOUNT";
				}
//ORIGINAL LINE: case "C000019A":
				else if (strErrorHex == "C000019A")
				{
						strErrorText = "STATUS_NOLOGON_SERVER_TRUST_ACCOUNT";
				}
//ORIGINAL LINE: case "C000019B":
				else if (strErrorHex == "C000019B")
				{
						strErrorText = "STATUS_DOMAIN_TRUST_INCONSISTENT";
				}
//ORIGINAL LINE: case "C000019C":
				else if (strErrorHex == "C000019C")
				{
						strErrorText = "STATUS_FS_DRIVER_REQUIRED";
				}
//ORIGINAL LINE: case "C0000202":
				else if (strErrorHex == "C0000202")
				{
						strErrorText = "STATUS_NO_USER_SESSION_KEY";
				}
//ORIGINAL LINE: case "C0000203":
				else if (strErrorHex == "C0000203")
				{
						strErrorText = "STATUS_USER_SESSION_DELETED";
				}
//ORIGINAL LINE: case "C0000204":
				else if (strErrorHex == "C0000204")
				{
						strErrorText = "STATUS_RESOURCE_LANG_NOT_FOUND";
				}
//ORIGINAL LINE: case "C0000205":
				else if (strErrorHex == "C0000205")
				{
						strErrorText = "STATUS_INSUFF_SERVER_RESOURCES";
				}
//ORIGINAL LINE: case "C0000206":
				else if (strErrorHex == "C0000206")
				{
						strErrorText = "STATUS_INVALID_BUFFER_SIZE";
				}
//ORIGINAL LINE: case "C0000207":
				else if (strErrorHex == "C0000207")
				{
						strErrorText = "STATUS_INVALID_ADDRESS_COMPONENT";
				}
//ORIGINAL LINE: case "C0000208":
				else if (strErrorHex == "C0000208")
				{
						strErrorText = "STATUS_INVALID_ADDRESS_WILDCARD";
				}
//ORIGINAL LINE: case "C0000209":
				else if (strErrorHex == "C0000209")
				{
						strErrorText = "STATUS_TOO_MANY_ADDRESSES";
				}
//ORIGINAL LINE: case "C000020A":
				else if (strErrorHex == "C000020A")
				{
						strErrorText = "STATUS_ADDRESS_ALREADY_EXISTS";
				}
//ORIGINAL LINE: case "C000020B":
				else if (strErrorHex == "C000020B")
				{
						strErrorText = "STATUS_ADDRESS_CLOSED";
				}
//ORIGINAL LINE: case "C000020C":
				else if (strErrorHex == "C000020C")
				{
						strErrorText = "STATUS_CONNECTION_DISCONNECTED";
				}
//ORIGINAL LINE: case "C000020D":
				else if (strErrorHex == "C000020D")
				{
						strErrorText = "STATUS_CONNECTION_RESET";
				}
//ORIGINAL LINE: case "C000020E":
				else if (strErrorHex == "C000020E")
				{
						strErrorText = "STATUS_TOO_MANY_NODES";
				}
//ORIGINAL LINE: case "C000020F":
				else if (strErrorHex == "C000020F")
				{
						strErrorText = "STATUS_TRANSACTION_ABORTED";
				}
//ORIGINAL LINE: case "C0000210":
				else if (strErrorHex == "C0000210")
				{
						strErrorText = "STATUS_TRANSACTION_TIMED_OUT";
				}
//ORIGINAL LINE: case "C0000211":
				else if (strErrorHex == "C0000211")
				{
						strErrorText = "STATUS_TRANSACTION_NO_RELEASE";
				}
//ORIGINAL LINE: case "C0000212":
				else if (strErrorHex == "C0000212")
				{
						strErrorText = "STATUS_TRANSACTION_NO_MATCH";
				}
//ORIGINAL LINE: case "C0000213":
				else if (strErrorHex == "C0000213")
				{
						strErrorText = "STATUS_TRANSACTION_RESPONDED";
				}
//ORIGINAL LINE: case "C0000214":
				else if (strErrorHex == "C0000214")
				{
						strErrorText = "STATUS_TRANSACTION_INVALID_ID";
				}
//ORIGINAL LINE: case "C0000215":
				else if (strErrorHex == "C0000215")
				{
						strErrorText = "STATUS_TRANSACTION_INVALID_TYPE";
				}
//ORIGINAL LINE: case "C0000216":
				else if (strErrorHex == "C0000216")
				{
						strErrorText = "STATUS_NOT_SERVER_SESSION";
				}
//ORIGINAL LINE: case "C0000217":
				else if (strErrorHex == "C0000217")
				{
						strErrorText = "STATUS_NOT_CLIENT_SESSION";
				}
//ORIGINAL LINE: case "C0000218":
				else if (strErrorHex == "C0000218")
				{
						strErrorText = "STATUS_CANNOT_LOAD_REGISTRY_FILE";
				}
//ORIGINAL LINE: case "C0000219":
				else if (strErrorHex == "C0000219")
				{
						strErrorText = "STATUS_DEBUG_ATTACH_FAILED";
				}
//ORIGINAL LINE: case "C000021A":
				else if (strErrorHex == "C000021A")
				{
						strErrorText = "STATUS_SYSTEM_PROCESS_TERMINATED";
				}
//ORIGINAL LINE: case "C000021B":
				else if (strErrorHex == "C000021B")
				{
						strErrorText = "STATUS_DATA_NOT_ACCEPTED";
				}
//ORIGINAL LINE: case "C000021C":
				else if (strErrorHex == "C000021C")
				{
						strErrorText = "STATUS_NO_BROWSER_SERVERS_FOUND";
				}
//ORIGINAL LINE: case "C000021D":
				else if (strErrorHex == "C000021D")
				{
						strErrorText = "STATUS_VDM_HARD_ERROR";
				}
//ORIGINAL LINE: case "C000021E":
				else if (strErrorHex == "C000021E")
				{
						strErrorText = "STATUS_DRIVER_CANCEL_TIMEOUT";
				}
//ORIGINAL LINE: case "C000021F":
				else if (strErrorHex == "C000021F")
				{
						strErrorText = "STATUS_REPLY_MESSAGE_MISMATCH";
				}
//ORIGINAL LINE: case "C0000220":
				else if (strErrorHex == "C0000220")
				{
						strErrorText = "STATUS_MAPPED_ALIGNMENT";
				}
//ORIGINAL LINE: case "C0000221":
				else if (strErrorHex == "C0000221")
				{
						strErrorText = "STATUS_IMAGE_CHECKSUM_MISMATCH";
				}
//ORIGINAL LINE: case "C0000222":
				else if (strErrorHex == "C0000222")
				{
						strErrorText = "STATUS_LOST_WRITEBEHIND_DATA";
				}
//ORIGINAL LINE: case "C0000223":
				else if (strErrorHex == "C0000223")
				{
						strErrorText = "STATUS_CLIENT_SERVER_PARAMETERS_INVALID";
				}
//ORIGINAL LINE: case "C0000224":
				else if (strErrorHex == "C0000224")
				{
						strErrorText = "STATUS_PASSWORD_MUST_CHANGE";
				}
//ORIGINAL LINE: case "C0000225":
				else if (strErrorHex == "C0000225")
				{
						strErrorText = "STATUS_NOT_FOUND";
				}
//ORIGINAL LINE: case "C0000226":
				else if (strErrorHex == "C0000226")
				{
						strErrorText = "STATUS_NOT_TINY_STREAM";
				}
//ORIGINAL LINE: case "C0000227":
				else if (strErrorHex == "C0000227")
				{
						strErrorText = "STATUS_RECOVERY_FAILURE";
				}
//ORIGINAL LINE: case "C0000228":
				else if (strErrorHex == "C0000228")
				{
						strErrorText = "STATUS_STACK_OVERFLOW_READ";
				}
//ORIGINAL LINE: case "C0000229":
				else if (strErrorHex == "C0000229")
				{
						strErrorText = "STATUS_FAIL_CHECK";
				}
//ORIGINAL LINE: case "C000022A":
				else if (strErrorHex == "C000022A")
				{
						strErrorText = "STATUS_DUPLICATE_OBJECTID";
				}
//ORIGINAL LINE: case "C000022B":
				else if (strErrorHex == "C000022B")
				{
						strErrorText = "STATUS_OBJECTID_EXISTS";
				}
//ORIGINAL LINE: case "C000022C":
				else if (strErrorHex == "C000022C")
				{
						strErrorText = "STATUS_CONVERT_TO_LARGE";
				}
//ORIGINAL LINE: case "C000022D":
				else if (strErrorHex == "C000022D")
				{
						strErrorText = "STATUS_RETRY";
				}
//ORIGINAL LINE: case "C000022E":
				else if (strErrorHex == "C000022E")
				{
						strErrorText = "STATUS_FOUND_OUT_OF_SCOPE";
				}
//ORIGINAL LINE: case "C000022F":
				else if (strErrorHex == "C000022F")
				{
						strErrorText = "STATUS_ALLOCATE_BUCKET";
				}
//ORIGINAL LINE: case "C0000230":
				else if (strErrorHex == "C0000230")
				{
						strErrorText = "STATUS_PROPSET_NOT_FOUND";
				}
//ORIGINAL LINE: case "C0000231":
				else if (strErrorHex == "C0000231")
				{
						strErrorText = "STATUS_MARSHALL_OVERFLOW";
				}
//ORIGINAL LINE: case "C0000232":
				else if (strErrorHex == "C0000232")
				{
						strErrorText = "STATUS_INVALID_VARIANT";
				}
//ORIGINAL LINE: case "C0000233":
				else if (strErrorHex == "C0000233")
				{
						strErrorText = "STATUS_DOMAIN_CONTROLLER_NOT_FOUND";
				}
//ORIGINAL LINE: case "C0000234":
				else if (strErrorHex == "C0000234")
				{
						strErrorText = "STATUS_ACCOUNT_LOCKED_OUT";
				}
//ORIGINAL LINE: case "C0000235":
				else if (strErrorHex == "C0000235")
				{
						strErrorText = "STATUS_HANDLE_NOT_CLOSABLE";
				}
//ORIGINAL LINE: case "C0000236":
				else if (strErrorHex == "C0000236")
				{
						strErrorText = "STATUS_CONNECTION_REFUSED";
				}
//ORIGINAL LINE: case "C0000237":
				else if (strErrorHex == "C0000237")
				{
						strErrorText = "STATUS_GRACEFUL_DISCONNECT";
				}
//ORIGINAL LINE: case "C0000238":
				else if (strErrorHex == "C0000238")
				{
						strErrorText = "STATUS_ADDRESS_ALREADY_ASSOCIATED";
				}
//ORIGINAL LINE: case "C0000239":
				else if (strErrorHex == "C0000239")
				{
						strErrorText = "STATUS_ADDRESS_NOT_ASSOCIATED";
				}
//ORIGINAL LINE: case "C000023A":
				else if (strErrorHex == "C000023A")
				{
						strErrorText = "STATUS_CONNECTION_INVALID";
				}
//ORIGINAL LINE: case "C000023B":
				else if (strErrorHex == "C000023B")
				{
						strErrorText = "STATUS_CONNECTION_ACTIVE";
				}
//ORIGINAL LINE: case "C000023C":
				else if (strErrorHex == "C000023C")
				{
						strErrorText = "STATUS_NETWORK_UNREACHABLE";
				}
//ORIGINAL LINE: case "C000023D":
				else if (strErrorHex == "C000023D")
				{
						strErrorText = "STATUS_HOST_UNREACHABLE";
				}
//ORIGINAL LINE: case "C000023E":
				else if (strErrorHex == "C000023E")
				{
						strErrorText = "STATUS_PROTOCOL_UNREACHABLE";
				}
//ORIGINAL LINE: case "C000023F":
				else if (strErrorHex == "C000023F")
				{
						strErrorText = "STATUS_PORT_UNREACHABLE";
				}
//ORIGINAL LINE: case "C0000240":
				else if (strErrorHex == "C0000240")
				{
						strErrorText = "STATUS_REQUEST_ABORTED";
				}
//ORIGINAL LINE: case "C0000241":
				else if (strErrorHex == "C0000241")
				{
						strErrorText = "STATUS_CONNECTION_ABORTED";
				}
//ORIGINAL LINE: case "C0000242":
				else if (strErrorHex == "C0000242")
				{
						strErrorText = "STATUS_BAD_COMPRESSION_BUFFER";
				}
//ORIGINAL LINE: case "C0000243":
				else if (strErrorHex == "C0000243")
				{
						strErrorText = "STATUS_USER_MAPPED_FILE";
				}
//ORIGINAL LINE: case "C0000244":
				else if (strErrorHex == "C0000244")
				{
						strErrorText = "STATUS_AUDIT_FAILED";
				}
//ORIGINAL LINE: case "C0000245":
				else if (strErrorHex == "C0000245")
				{
						strErrorText = "STATUS_TIMER_RESOLUTION_NOT_SET";
				}
//ORIGINAL LINE: case "C0000246":
				else if (strErrorHex == "C0000246")
				{
						strErrorText = "STATUS_CONNECTION_COUNT_LIMIT";
				}
//ORIGINAL LINE: case "C0000247":
				else if (strErrorHex == "C0000247")
				{
						strErrorText = "STATUS_LOGIN_TIME_RESTRICTION";
				}
//ORIGINAL LINE: case "C0000248":
				else if (strErrorHex == "C0000248")
				{
						strErrorText = "STATUS_LOGIN_WKSTA_RESTRICTION";
				}
//ORIGINAL LINE: case "C0000249":
				else if (strErrorHex == "C0000249")
				{
						strErrorText = "STATUS_IMAGE_MP_UP_MISMATCH";
				}
//ORIGINAL LINE: case "C0000250":
				else if (strErrorHex == "C0000250")
				{
						strErrorText = "STATUS_INSUFFICIENT_LOGON_INFO";
				}
//ORIGINAL LINE: case "C0000251":
				else if (strErrorHex == "C0000251")
				{
						strErrorText = "STATUS_BAD_DLL_ENTRYPOINT";
				}
//ORIGINAL LINE: case "C0000252":
				else if (strErrorHex == "C0000252")
				{
						strErrorText = "STATUS_BAD_SERVICE_ENTRYPOINT";
				}
//ORIGINAL LINE: case "C0000253":
				else if (strErrorHex == "C0000253")
				{
						strErrorText = "STATUS_LPC_REPLY_LOST";
				}
//ORIGINAL LINE: case "C0000254":
				else if (strErrorHex == "C0000254")
				{
						strErrorText = "STATUS_IP_ADDRESS_CONFLICT1";
				}
//ORIGINAL LINE: case "C0000255":
				else if (strErrorHex == "C0000255")
				{
						strErrorText = "STATUS_IP_ADDRESS_CONFLICT2";
				}
//ORIGINAL LINE: case "C0000256":
				else if (strErrorHex == "C0000256")
				{
						strErrorText = "STATUS_REGISTRY_QUOTA_LIMIT";
				}
//ORIGINAL LINE: case "C0000257":
				else if (strErrorHex == "C0000257")
				{
						strErrorText = "STATUS_PATH_NOT_COVERED";
				}
//ORIGINAL LINE: case "C0000258":
				else if (strErrorHex == "C0000258")
				{
						strErrorText = "STATUS_NO_CALLBACK_ACTIVE";
				}
//ORIGINAL LINE: case "C0000259":
				else if (strErrorHex == "C0000259")
				{
						strErrorText = "STATUS_LICENSE_QUOTA_EXCEEDED";
				}
//ORIGINAL LINE: case "C000025A":
				else if (strErrorHex == "C000025A")
				{
						strErrorText = "STATUS_PWD_TOO_SHORT";
				}
//ORIGINAL LINE: case "C000025B":
				else if (strErrorHex == "C000025B")
				{
						strErrorText = "STATUS_PWD_TOO_RECENT";
				}
//ORIGINAL LINE: case "C000025C":
				else if (strErrorHex == "C000025C")
				{
						strErrorText = "STATUS_PWD_HISTORY_CONFLICT";
				}
//ORIGINAL LINE: case "C000025E":
				else if (strErrorHex == "C000025E")
				{
						strErrorText = "STATUS_PLUGPLAY_NO_DEVICE";
				}
//ORIGINAL LINE: case "C000025F":
				else if (strErrorHex == "C000025F")
				{
						strErrorText = "STATUS_UNSUPPORTED_COMPRESSION";
				}
//ORIGINAL LINE: case "C0000260":
				else if (strErrorHex == "C0000260")
				{
						strErrorText = "STATUS_INVALID_HW_PROFILE";
				}
//ORIGINAL LINE: case "C0000261":
				else if (strErrorHex == "C0000261")
				{
						strErrorText = "STATUS_INVALID_PLUGPLAY_DEVICE_PATH";
				}
//ORIGINAL LINE: case "C0000262":
				else if (strErrorHex == "C0000262")
				{
						strErrorText = "STATUS_DRIVER_ORDINAL_NOT_FOUND";
				}
//ORIGINAL LINE: case "C0000263":
				else if (strErrorHex == "C0000263")
				{
						strErrorText = "STATUS_DRIVER_ENTRYPOINT_NOT_FOUND";
				}
//ORIGINAL LINE: case "C0000264":
				else if (strErrorHex == "C0000264")
				{
						strErrorText = "STATUS_RESOURCE_NOT_OWNED";
				}
//ORIGINAL LINE: case "C0000265":
				else if (strErrorHex == "C0000265")
				{
						strErrorText = "STATUS_TOO_MANY_LINKS";
				}
//ORIGINAL LINE: case "C0000266":
				else if (strErrorHex == "C0000266")
				{
						strErrorText = "STATUS_QUOTA_LIST_INCONSISTENT";
				}
//ORIGINAL LINE: case "C0000267":
				else if (strErrorHex == "C0000267")
				{
						strErrorText = "STATUS_FILE_IS_OFFLINE";
				}
//ORIGINAL LINE: case "C0000268":
				else if (strErrorHex == "C0000268")
				{
						strErrorText = "STATUS_EVALUATION_EXPIRATION";
				}
//ORIGINAL LINE: case "C0000269":
				else if (strErrorHex == "C0000269")
				{
						strErrorText = "STATUS_ILLEGAL_DLL_RELOCATION";
				}
//ORIGINAL LINE: case "C000026A":
				else if (strErrorHex == "C000026A")
				{
						strErrorText = "STATUS_LICENSE_VIOLATION";
				}
//ORIGINAL LINE: case "C000026B":
				else if (strErrorHex == "C000026B")
				{
						strErrorText = "STATUS_DLL_INIT_FAILED_LOGOFF";
				}
//ORIGINAL LINE: case "C000026C":
				else if (strErrorHex == "C000026C")
				{
						strErrorText = "STATUS_DRIVER_UNABLE_TO_LOAD";
				}
//ORIGINAL LINE: case "C000026D":
				else if (strErrorHex == "C000026D")
				{
						strErrorText = "STATUS_DFS_UNAVAILABLE";
				}
//ORIGINAL LINE: case "C000026E":
				else if (strErrorHex == "C000026E")
				{
						strErrorText = "STATUS_VOLUME_DISMOUNTED";
				}
//ORIGINAL LINE: case "C000026F":
				else if (strErrorHex == "C000026F")
				{
						strErrorText = "STATUS_WX86_INTERNAL_ERROR";
				}
//ORIGINAL LINE: case "C0000270":
				else if (strErrorHex == "C0000270")
				{
						strErrorText = "STATUS_WX86_FLOAT_STACK_CHECK";
				}
//ORIGINAL LINE: case "C0000271":
				else if (strErrorHex == "C0000271")
				{
						strErrorText = "STATUS_VALIDATE_CONTINUE";
				}
//ORIGINAL LINE: case "C0000272":
				else if (strErrorHex == "C0000272")
				{
						strErrorText = "STATUS_NO_MATCH";
				}
//ORIGINAL LINE: case "C0000273":
				else if (strErrorHex == "C0000273")
				{
						strErrorText = "STATUS_NO_MORE_MATCHES";
				}
//ORIGINAL LINE: case "C0000275":
				else if (strErrorHex == "C0000275")
				{
						strErrorText = "STATUS_NOT_A_REPARSE_POINT";
				}
//ORIGINAL LINE: case "C0000276":
				else if (strErrorHex == "C0000276")
				{
						strErrorText = "STATUS_IO_REPARSE_TAG_INVALID";
				}
//ORIGINAL LINE: case "C0000277":
				else if (strErrorHex == "C0000277")
				{
						strErrorText = "STATUS_IO_REPARSE_TAG_MISMATCH";
				}
//ORIGINAL LINE: case "C0000278":
				else if (strErrorHex == "C0000278")
				{
						strErrorText = "STATUS_IO_REPARSE_DATA_INVALID";
				}
//ORIGINAL LINE: case "C0000279":
				else if (strErrorHex == "C0000279")
				{
						strErrorText = "STATUS_IO_REPARSE_TAG_NOT_HANDLED";
				}
//ORIGINAL LINE: case "C0000280":
				else if (strErrorHex == "C0000280")
				{
						strErrorText = "STATUS_REPARSE_POINT_NOT_RESOLVED";
				}
//ORIGINAL LINE: case "C0000281":
				else if (strErrorHex == "C0000281")
				{
						strErrorText = "STATUS_DIRECTORY_IS_A_REPARSE_POINT";
				}
//ORIGINAL LINE: case "C0000282":
				else if (strErrorHex == "C0000282")
				{
						strErrorText = "STATUS_RANGE_LIST_CONFLICT";
				}
//ORIGINAL LINE: case "C0000283":
				else if (strErrorHex == "C0000283")
				{
						strErrorText = "STATUS_SOURCE_ELEMENT_EMPTY";
				}
//ORIGINAL LINE: case "C0000284":
				else if (strErrorHex == "C0000284")
				{
						strErrorText = "STATUS_DESTINATION_ELEMENT_FULL";
				}
//ORIGINAL LINE: case "C0000285":
				else if (strErrorHex == "C0000285")
				{
						strErrorText = "STATUS_ILLEGAL_ELEMENT_ADDRESS";
				}
//ORIGINAL LINE: case "C0000286":
				else if (strErrorHex == "C0000286")
				{
						strErrorText = "STATUS_MAGAZINE_NOT_PRESENT";
				}
//ORIGINAL LINE: case "C0000287":
				else if (strErrorHex == "C0000287")
				{
						strErrorText = "STATUS_REINITIALIZATION_NEEDED";
				}
//ORIGINAL LINE: case "80000288":
				else if (strErrorHex == "80000288")
				{
						strErrorText = "STATUS_DEVICE_REQUIRES_CLEANING";
				}
//ORIGINAL LINE: case "80000289":
				else if (strErrorHex == "80000289")
				{
						strErrorText = "STATUS_DEVICE_DOOR_OPEN";
				}
//ORIGINAL LINE: case "C000028A":
				else if (strErrorHex == "C000028A")
				{
						strErrorText = "STATUS_ENCRYPTION_FAILED";
				}
//ORIGINAL LINE: case "C000028B":
				else if (strErrorHex == "C000028B")
				{
						strErrorText = "STATUS_DECRYPTION_FAILED";
				}
//ORIGINAL LINE: case "C000028C":
				else if (strErrorHex == "C000028C")
				{
						strErrorText = "STATUS_RANGE_NOT_FOUND";
				}
//ORIGINAL LINE: case "C000028D":
				else if (strErrorHex == "C000028D")
				{
						strErrorText = "STATUS_NO_RECOVERY_POLICY";
				}
//ORIGINAL LINE: case "C000028E":
				else if (strErrorHex == "C000028E")
				{
						strErrorText = "STATUS_NO_EFS";
				}
//ORIGINAL LINE: case "C000028F":
				else if (strErrorHex == "C000028F")
				{
						strErrorText = "STATUS_WRONG_EFS";
				}
//ORIGINAL LINE: case "C0000290":
				else if (strErrorHex == "C0000290")
				{
						strErrorText = "STATUS_NO_USER_KEYS";
				}
//ORIGINAL LINE: case "C0000291":
				else if (strErrorHex == "C0000291")
				{
						strErrorText = "STATUS_FILE_NOT_ENCRYPTED";
				}
//ORIGINAL LINE: case "C0000292":
				else if (strErrorHex == "C0000292")
				{
						strErrorText = "STATUS_NOT_EXPORT_FORMAT";
				}
//ORIGINAL LINE: case "C0000293":
				else if (strErrorHex == "C0000293")
				{
						strErrorText = "STATUS_FILE_ENCRYPTED";
				}
//ORIGINAL LINE: case "40000294":
				else if (strErrorHex == "40000294")
				{
						strErrorText = "STATUS_WAKE_SYSTEM";
				}
//ORIGINAL LINE: case "C0000295":
				else if (strErrorHex == "C0000295")
				{
						strErrorText = "STATUS_WMI_GUID_NOT_FOUND";
				}
//ORIGINAL LINE: case "C0000296":
				else if (strErrorHex == "C0000296")
				{
						strErrorText = "STATUS_WMI_INSTANCE_NOT_FOUND";
				}
//ORIGINAL LINE: case "C0000297":
				else if (strErrorHex == "C0000297")
				{
						strErrorText = "STATUS_WMI_ITEMID_NOT_FOUND";
				}
//ORIGINAL LINE: case "C0000298":
				else if (strErrorHex == "C0000298")
				{
						strErrorText = "STATUS_WMI_TRY_AGAIN";
				}
//ORIGINAL LINE: case "C0000299":
				else if (strErrorHex == "C0000299")
				{
						strErrorText = "STATUS_SHARED_POLICY";
				}
//ORIGINAL LINE: case "C000029A":
				else if (strErrorHex == "C000029A")
				{
						strErrorText = "STATUS_POLICY_OBJECT_NOT_FOUND";
				}
//ORIGINAL LINE: case "C000029B":
				else if (strErrorHex == "C000029B")
				{
						strErrorText = "STATUS_POLICY_ONLY_IN_DS";
				}
//ORIGINAL LINE: case "C000029C":
				else if (strErrorHex == "C000029C")
				{
						strErrorText = "STATUS_VOLUME_NOT_UPGRADED";
				}
//ORIGINAL LINE: case "C000029D":
				else if (strErrorHex == "C000029D")
				{
						strErrorText = "STATUS_REMOTE_STORAGE_NOT_ACTIVE";
				}
//ORIGINAL LINE: case "C000029E":
				else if (strErrorHex == "C000029E")
				{
						strErrorText = "STATUS_REMOTE_STORAGE_MEDIA_ERROR";
				}
//ORIGINAL LINE: case "C000029F":
				else if (strErrorHex == "C000029F")
				{
						strErrorText = "STATUS_NO_TRACKING_SERVICE";
				}
//ORIGINAL LINE: case "C00002A0":
				else if (strErrorHex == "C00002A0")
				{
						strErrorText = "STATUS_SERVER_SID_MISMATCH";
				}
//ORIGINAL LINE: case "C00002A1":
				else if (strErrorHex == "C00002A1")
				{
						strErrorText = "STATUS_DS_NO_ATTRIBUTE_OR_VALUE";
				}
//ORIGINAL LINE: case "C00002A2":
				else if (strErrorHex == "C00002A2")
				{
						strErrorText = "STATUS_DS_INVALID_ATTRIBUTE_SYNTAX";
				}
//ORIGINAL LINE: case "C00002A3":
				else if (strErrorHex == "C00002A3")
				{
						strErrorText = "STATUS_DS_ATTRIBUTE_TYPE_UNDEFINED";
				}
//ORIGINAL LINE: case "C00002A4":
				else if (strErrorHex == "C00002A4")
				{
						strErrorText = "STATUS_DS_ATTRIBUTE_OR_VALUE_EXISTS";
				}
//ORIGINAL LINE: case "C00002A5":
				else if (strErrorHex == "C00002A5")
				{
						strErrorText = "STATUS_DS_BUSY";
				}
//ORIGINAL LINE: case "C00002A6":
				else if (strErrorHex == "C00002A6")
				{
						strErrorText = "STATUS_DS_UNAVAILABLE";
				}
//ORIGINAL LINE: case "C00002A7":
				else if (strErrorHex == "C00002A7")
				{
						strErrorText = "STATUS_DS_NO_RIDS_ALLOCATED";
				}
//ORIGINAL LINE: case "C00002A8":
				else if (strErrorHex == "C00002A8")
				{
						strErrorText = "STATUS_DS_NO_MORE_RIDS";
				}
//ORIGINAL LINE: case "C00002A9":
				else if (strErrorHex == "C00002A9")
				{
						strErrorText = "STATUS_DS_INCORRECT_ROLE_OWNER";
				}
//ORIGINAL LINE: case "C00002AA":
				else if (strErrorHex == "C00002AA")
				{
						strErrorText = "STATUS_DS_RIDMGR_INIT_ERROR";
				}
//ORIGINAL LINE: case "C00002AB":
				else if (strErrorHex == "C00002AB")
				{
						strErrorText = "STATUS_DS_OBJ_CLASS_VIOLATION";
				}
//ORIGINAL LINE: case "C00002AC":
				else if (strErrorHex == "C00002AC")
				{
						strErrorText = "STATUS_DS_CANT_ON_NON_LEAF";
				}
//ORIGINAL LINE: case "C00002AD":
				else if (strErrorHex == "C00002AD")
				{
						strErrorText = "STATUS_DS_CANT_ON_RDN";
				}
//ORIGINAL LINE: case "C00002AE":
				else if (strErrorHex == "C00002AE")
				{
						strErrorText = "STATUS_DS_CANT_MOD_OBJ_CLASS";
				}
//ORIGINAL LINE: case "C00002AF":
				else if (strErrorHex == "C00002AF")
				{
						strErrorText = "STATUS_DS_CROSS_DOM_MOVE_FAILED";
				}
//ORIGINAL LINE: case "C00002B0":
				else if (strErrorHex == "C00002B0")
				{
						strErrorText = "STATUS_DS_GC_NOT_AVAILABLE";
				}
//ORIGINAL LINE: case "C00002B1":
				else if (strErrorHex == "C00002B1")
				{
						strErrorText = "STATUS_DIRECTORY_SERVICE_REQUIRED";
				}
//ORIGINAL LINE: case "C00002B2":
				else if (strErrorHex == "C00002B2")
				{
						strErrorText = "STATUS_REPARSE_ATTRIBUTE_CONFLICT";
				}
//ORIGINAL LINE: case "C00002B3":
				else if (strErrorHex == "C00002B3")
				{
						strErrorText = "STATUS_CANT_ENABLE_DENY_ONLY";
				}
//ORIGINAL LINE: case "C00002B4":
				else if (strErrorHex == "C00002B4")
				{
						strErrorText = "STATUS_FLOAT_MULTIPLE_FAULTS";
				}
//ORIGINAL LINE: case "C00002B5":
				else if (strErrorHex == "C00002B5")
				{
						strErrorText = "STATUS_FLOAT_MULTIPLE_TRAPS";
				}
//ORIGINAL LINE: case "C00002B6":
				else if (strErrorHex == "C00002B6")
				{
						strErrorText = "STATUS_DEVICE_REMOVED";
				}
//ORIGINAL LINE: case "C00002B7":
				else if (strErrorHex == "C00002B7")
				{
						strErrorText = "STATUS_JOURNAL_DELETE_IN_PROGRESS";
				}
//ORIGINAL LINE: case "C00002B8":
				else if (strErrorHex == "C00002B8")
				{
						strErrorText = "STATUS_JOURNAL_NOT_ACTIVE";
				}
//ORIGINAL LINE: case "C00002B9":
				else if (strErrorHex == "C00002B9")
				{
						strErrorText = "STATUS_NOINTERFACE";
				}
//ORIGINAL LINE: case "C00002C1":
				else if (strErrorHex == "C00002C1")
				{
						strErrorText = "STATUS_DS_ADMIN_LIMIT_EXCEEDED";
				}
//ORIGINAL LINE: case "C00002C2":
				else if (strErrorHex == "C00002C2")
				{
						strErrorText = "STATUS_DRIVER_FAILED_SLEEP";
				}
//ORIGINAL LINE: case "C00002C3":
				else if (strErrorHex == "C00002C3")
				{
						strErrorText = "STATUS_MUTUAL_AUTHENTICATION_FAILED";
				}
//ORIGINAL LINE: case "C00002C4":
				else if (strErrorHex == "C00002C4")
				{
						strErrorText = "STATUS_CORRUPT_SYSTEM_FILE";
				}
//ORIGINAL LINE: case "C00002C5":
				else if (strErrorHex == "C00002C5")
				{
						strErrorText = "STATUS_DATATYPE_MISALIGNMENT_ERROR";
				}
//ORIGINAL LINE: case "C00002C6":
				else if (strErrorHex == "C00002C6")
				{
						strErrorText = "STATUS_WMI_READ_ONLY";
				}
//ORIGINAL LINE: case "C00002C7":
				else if (strErrorHex == "C00002C7")
				{
						strErrorText = "STATUS_WMI_SET_FAILURE";
				}
//ORIGINAL LINE: case "C00002C8":
				else if (strErrorHex == "C00002C8")
				{
						strErrorText = "STATUS_COMMITMENT_MINIMUM";
				}
//ORIGINAL LINE: case "C00002C9":
				else if (strErrorHex == "C00002C9")
				{
						strErrorText = "STATUS_REG_NAT_CONSUMPTION";
				}
//ORIGINAL LINE: case "C00002CA":
				else if (strErrorHex == "C00002CA")
				{
						strErrorText = "STATUS_TRANSPORT_FULL";
				}
//ORIGINAL LINE: case "C00002CB":
				else if (strErrorHex == "C00002CB")
				{
						strErrorText = "STATUS_DS_SAM_INIT_FAILURE";
				}
//ORIGINAL LINE: case "C00002CC":
				else if (strErrorHex == "C00002CC")
				{
						strErrorText = "STATUS_ONLY_IF_CONNECTED";
				}
//ORIGINAL LINE: case "C00002CD":
				else if (strErrorHex == "C00002CD")
				{
						strErrorText = "STATUS_DS_SENSITIVE_GROUP_VIOLATION";
				}
//ORIGINAL LINE: case "C00002CE":
				else if (strErrorHex == "C00002CE")
				{
						strErrorText = "STATUS_PNP_RESTART_ENUMERATION";
				}
//ORIGINAL LINE: case "C00002CF":
				else if (strErrorHex == "C00002CF")
				{
						strErrorText = "STATUS_JOURNAL_ENTRY_DELETED";
				}
//ORIGINAL LINE: case "C00002D0":
				else if (strErrorHex == "C00002D0")
				{
						strErrorText = "STATUS_DS_CANT_MOD_PRIMARYGROUPID";
				}
//ORIGINAL LINE: case "C00002D1":
				else if (strErrorHex == "C00002D1")
				{
						strErrorText = "STATUS_SYSTEM_IMAGE_BAD_SIGNATURE";
				}
//ORIGINAL LINE: case "C00002D2":
				else if (strErrorHex == "C00002D2")
				{
						strErrorText = "STATUS_PNP_REBOOT_REQUIRED";
				}
//ORIGINAL LINE: case "C00002D3":
				else if (strErrorHex == "C00002D3")
				{
						strErrorText = "STATUS_POWER_STATE_INVALID";
				}
//ORIGINAL LINE: case "C00002D4":
				else if (strErrorHex == "C00002D4")
				{
						strErrorText = "STATUS_DS_INVALID_GROUP_TYPE";
				}
//ORIGINAL LINE: case "C00002D5":
				else if (strErrorHex == "C00002D5")
				{
						strErrorText = "STATUS_DS_NO_NEST_GLOBALGROUP_IN_MIXEDDOMAIN";
				}
//ORIGINAL LINE: case "C00002D6":
				else if (strErrorHex == "C00002D6")
				{
						strErrorText = "STATUS_DS_NO_NEST_LOCALGROUP_IN_MIXEDDOMAIN";
				}
//ORIGINAL LINE: case "C00002D7":
				else if (strErrorHex == "C00002D7")
				{
						strErrorText = "STATUS_DS_GLOBAL_CANT_HAVE_LOCAL_MEMBER";
				}
//ORIGINAL LINE: case "C00002D8":
				else if (strErrorHex == "C00002D8")
				{
						strErrorText = "STATUS_DS_GLOBAL_CANT_HAVE_UNIVERSAL_MEMBER";
				}
//ORIGINAL LINE: case "C00002D9":
				else if (strErrorHex == "C00002D9")
				{
						strErrorText = "STATUS_DS_UNIVERSAL_CANT_HAVE_LOCAL_MEMBER";
				}
//ORIGINAL LINE: case "C00002DA":
				else if (strErrorHex == "C00002DA")
				{
						strErrorText = "STATUS_DS_GLOBAL_CANT_HAVE_CROSSDOMAIN_MEMBER";
				}
//ORIGINAL LINE: case "C00002DB":
				else if (strErrorHex == "C00002DB")
				{
						strErrorText = "STATUS_DS_LOCAL_CANT_HAVE_CROSSDOMAIN_LOCAL_MEMBER";
				}
//ORIGINAL LINE: case "C00002DC":
				else if (strErrorHex == "C00002DC")
				{
						strErrorText = "STATUS_DS_HAVE_PRIMARY_MEMBERS";
				}
//ORIGINAL LINE: case "C00002DD":
				else if (strErrorHex == "C00002DD")
				{
						strErrorText = "STATUS_WMI_NOT_SUPPORTED";
				}
//ORIGINAL LINE: case "C00002DE":
				else if (strErrorHex == "C00002DE")
				{
						strErrorText = "STATUS_INSUFFICIENT_POWER";
				}
//ORIGINAL LINE: case "C00002DF":
				else if (strErrorHex == "C00002DF")
				{
						strErrorText = "STATUS_SAM_NEED_BOOTKEY_PASSWORD";
				}
//ORIGINAL LINE: case "C00002E0":
				else if (strErrorHex == "C00002E0")
				{
						strErrorText = "STATUS_SAM_NEED_BOOTKEY_FLOPPY";
				}
//ORIGINAL LINE: case "C00002E1":
				else if (strErrorHex == "C00002E1")
				{
						strErrorText = "STATUS_DS_CANT_START";
				}
//ORIGINAL LINE: case "C00002E2":
				else if (strErrorHex == "C00002E2")
				{
						strErrorText = "STATUS_DS_INIT_FAILURE";
				}
//ORIGINAL LINE: case "C00002E3":
				else if (strErrorHex == "C00002E3")
				{
						strErrorText = "STATUS_SAM_INIT_FAILURE";
				}
//ORIGINAL LINE: case "C00002E4":
				else if (strErrorHex == "C00002E4")
				{
						strErrorText = "STATUS_DS_GC_REQUIRED";
				}
//ORIGINAL LINE: case "C00002E5":
				else if (strErrorHex == "C00002E5")
				{
						strErrorText = "STATUS_DS_LOCAL_MEMBER_OF_LOCAL_ONLY";
				}
//ORIGINAL LINE: case "C00002E6":
				else if (strErrorHex == "C00002E6")
				{
						strErrorText = "STATUS_DS_NO_FPO_IN_UNIVERSAL_GROUPS";
				}
//ORIGINAL LINE: case "C00002E7":
				else if (strErrorHex == "C00002E7")
				{
						strErrorText = "STATUS_DS_MACHINE_ACCOUNT_QUOTA_EXCEEDED";
				}
//ORIGINAL LINE: case "C00002E8":
				else if (strErrorHex == "C00002E8")
				{
						strErrorText = "STATUS_MULTIPLE_FAULT_VIOLATION";
				}
//ORIGINAL LINE: case "C00002E9":
				else if (strErrorHex == "C00002E9")
				{
						strErrorText = "STATUS_CURRENT_DOMAIN_NOT_ALLOWED";
				}
//ORIGINAL LINE: case "C00002EA":
				else if (strErrorHex == "C00002EA")
				{
						strErrorText = "STATUS_CANNOT_MAKE";
				}
//ORIGINAL LINE: case "C00002EB":
				else if (strErrorHex == "C00002EB")
				{
						strErrorText = "STATUS_SYSTEM_SHUTDOWN";
				}
//ORIGINAL LINE: case "C00002EC":
				else if (strErrorHex == "C00002EC")
				{
						strErrorText = "STATUS_DS_INIT_FAILURE_CONSOLE";
				}
//ORIGINAL LINE: case "C00002ED":
				else if (strErrorHex == "C00002ED")
				{
						strErrorText = "STATUS_DS_SAM_INIT_FAILURE_CONSOLE";
				}
//ORIGINAL LINE: case "C00002EE":
				else if (strErrorHex == "C00002EE")
				{
						strErrorText = "STATUS_UNFINISHED_CONTEXT_DELETED";
				}
//ORIGINAL LINE: case "C00002EF":
				else if (strErrorHex == "C00002EF")
				{
						strErrorText = "STATUS_NO_TGT_REPLY";
				}
//ORIGINAL LINE: case "C00002F0":
				else if (strErrorHex == "C00002F0")
				{
						strErrorText = "STATUS_OBJECTID_NOT_FOUND";
				}
//ORIGINAL LINE: case "C00002F1":
				else if (strErrorHex == "C00002F1")
				{
						strErrorText = "STATUS_NO_IP_ADDRESSES";
				}
//ORIGINAL LINE: case "C00002F2":
				else if (strErrorHex == "C00002F2")
				{
						strErrorText = "STATUS_WRONG_CREDENTIAL_HANDLE";
				}
//ORIGINAL LINE: case "C00002F3":
				else if (strErrorHex == "C00002F3")
				{
						strErrorText = "STATUS_CRYPTO_SYSTEM_INVALID";
				}
//ORIGINAL LINE: case "C00002F4":
				else if (strErrorHex == "C00002F4")
				{
						strErrorText = "STATUS_MAX_REFERRALS_EXCEEDED";
				}
//ORIGINAL LINE: case "C00002F5":
				else if (strErrorHex == "C00002F5")
				{
						strErrorText = "STATUS_MUST_BE_KDC";
				}
//ORIGINAL LINE: case "C00002F6":
				else if (strErrorHex == "C00002F6")
				{
						strErrorText = "STATUS_STRONG_CRYPTO_NOT_SUPPORTED";
				}
//ORIGINAL LINE: case "C00002F7":
				else if (strErrorHex == "C00002F7")
				{
						strErrorText = "STATUS_TOO_MANY_PRINCIPALS";
				}
//ORIGINAL LINE: case "C00002F8":
				else if (strErrorHex == "C00002F8")
				{
						strErrorText = "STATUS_NO_PA_DATA";
				}
//ORIGINAL LINE: case "C00002F9":
				else if (strErrorHex == "C00002F9")
				{
						strErrorText = "STATUS_PKINIT_NAME_MISMATCH";
				}
//ORIGINAL LINE: case "C00002FA":
				else if (strErrorHex == "C00002FA")
				{
						strErrorText = "STATUS_SMARTCARD_LOGON_REQUIRED";
				}
//ORIGINAL LINE: case "C00002FB":
				else if (strErrorHex == "C00002FB")
				{
						strErrorText = "STATUS_KDC_INVALID_REQUEST";
				}
//ORIGINAL LINE: case "C00002FC":
				else if (strErrorHex == "C00002FC")
				{
						strErrorText = "STATUS_KDC_UNABLE_TO_REFER";
				}
//ORIGINAL LINE: case "C00002FD":
				else if (strErrorHex == "C00002FD")
				{
						strErrorText = "STATUS_KDC_UNKNOWN_ETYPE";
				}
//ORIGINAL LINE: case "C00002FE":
				else if (strErrorHex == "C00002FE")
				{
						strErrorText = "STATUS_SHUTDOWN_IN_PROGRESS";
				}
//ORIGINAL LINE: case "C00002FF":
				else if (strErrorHex == "C00002FF")
				{
						strErrorText = "STATUS_SERVER_SHUTDOWN_IN_PROGRESS";
				}
//ORIGINAL LINE: case "C0000300":
				else if (strErrorHex == "C0000300")
				{
						strErrorText = "STATUS_NOT_SUPPORTED_ON_SBS";
				}
//ORIGINAL LINE: case "C0000301":
				else if (strErrorHex == "C0000301")
				{
						strErrorText = "STATUS_WMI_GUID_DISCONNECTED";
				}
//ORIGINAL LINE: case "C0000302":
				else if (strErrorHex == "C0000302")
				{
						strErrorText = "STATUS_WMI_ALREADY_DISABLED";
				}
//ORIGINAL LINE: case "C0000303":
				else if (strErrorHex == "C0000303")
				{
						strErrorText = "STATUS_WMI_ALREADY_ENABLED";
				}
//ORIGINAL LINE: case "C0000304":
				else if (strErrorHex == "C0000304")
				{
						strErrorText = "STATUS_MFT_TOO_FRAGMENTED";
				}
//ORIGINAL LINE: case "C0000305":
				else if (strErrorHex == "C0000305")
				{
						strErrorText = "STATUS_COPY_PROTECTION_FAILURE";
				}
//ORIGINAL LINE: case "C0000306":
				else if (strErrorHex == "C0000306")
				{
						strErrorText = "STATUS_CSS_AUTHENTICATION_FAILURE";
				}
//ORIGINAL LINE: case "C0000307":
				else if (strErrorHex == "C0000307")
				{
						strErrorText = "STATUS_CSS_KEY_NOT_PRESENT";
				}
//ORIGINAL LINE: case "C0000308":
				else if (strErrorHex == "C0000308")
				{
						strErrorText = "STATUS_CSS_KEY_NOT_ESTABLISHED";
				}
//ORIGINAL LINE: case "C0000309":
				else if (strErrorHex == "C0000309")
				{
						strErrorText = "STATUS_CSS_SCRAMBLED_SECTOR";
				}
//ORIGINAL LINE: case "C000030A":
				else if (strErrorHex == "C000030A")
				{
						strErrorText = "STATUS_CSS_REGION_MISMATCH";
				}
//ORIGINAL LINE: case "C000030B":
				else if (strErrorHex == "C000030B")
				{
						strErrorText = "STATUS_CSS_RESETS_EXHAUSTED";
				}
//ORIGINAL LINE: case "C0000320":
				else if (strErrorHex == "C0000320")
				{
						strErrorText = "STATUS_PKINIT_FAILURE";
				}
//ORIGINAL LINE: case "C0000321":
				else if (strErrorHex == "C0000321")
				{
						strErrorText = "STATUS_SMARTCARD_SUBSYSTEM_FAILURE";
				}
//ORIGINAL LINE: case "C0000322":
				else if (strErrorHex == "C0000322")
				{
						strErrorText = "STATUS_NO_KERB_KEY";
				}
//ORIGINAL LINE: case "C0000350":
				else if (strErrorHex == "C0000350")
				{
						strErrorText = "STATUS_HOST_DOWN";
				}
//ORIGINAL LINE: case "C0000351":
				else if (strErrorHex == "C0000351")
				{
						strErrorText = "STATUS_UNSUPPORTED_PREAUTH";
				}
//ORIGINAL LINE: case "C0000352":
				else if (strErrorHex == "C0000352")
				{
						strErrorText = "STATUS_EFS_ALG_BLOB_TOO_BIG";
				}
//ORIGINAL LINE: case "C0000353":
				else if (strErrorHex == "C0000353")
				{
						strErrorText = "STATUS_PORT_NOT_SET";
				}
//ORIGINAL LINE: case "C0000354":
				else if (strErrorHex == "C0000354")
				{
						strErrorText = "STATUS_DEBUGGER_INACTIVE";
				}
//ORIGINAL LINE: case "C0000355":
				else if (strErrorHex == "C0000355")
				{
						strErrorText = "STATUS_DS_VERSION_CHECK_FAILURE";
				}
//ORIGINAL LINE: case "C0000356":
				else if (strErrorHex == "C0000356")
				{
						strErrorText = "STATUS_AUDITING_DISABLED";
				}
//ORIGINAL LINE: case "C0000357":
				else if (strErrorHex == "C0000357")
				{
						strErrorText = "STATUS_PRENT4_MACHINE_ACCOUNT";
				}
//ORIGINAL LINE: case "C0000358":
				else if (strErrorHex == "C0000358")
				{
						strErrorText = "STATUS_DS_AG_CANT_HAVE_UNIVERSAL_MEMBER";
				}
//ORIGINAL LINE: case "C0000359":
				else if (strErrorHex == "C0000359")
				{
						strErrorText = "STATUS_INVALID_IMAGE_WIN_32";
				}
//ORIGINAL LINE: case "C000035A":
				else if (strErrorHex == "C000035A")
				{
						strErrorText = "STATUS_INVALID_IMAGE_WIN_64";
				}
//ORIGINAL LINE: case "C000035B":
				else if (strErrorHex == "C000035B")
				{
						strErrorText = "STATUS_BAD_BINDINGS";
				}
//ORIGINAL LINE: case "C000035C":
				else if (strErrorHex == "C000035C")
				{
						strErrorText = "STATUS_NETWORK_SESSION_EXPIRED";
				}
//ORIGINAL LINE: case "C000035D":
				else if (strErrorHex == "C000035D")
				{
						strErrorText = "STATUS_APPHELP_BLOCK";
				}
//ORIGINAL LINE: case "C000035E":
				else if (strErrorHex == "C000035E")
				{
						strErrorText = "STATUS_ALL_SIDS_FILTERED";
				}
//ORIGINAL LINE: case "C000035F":
				else if (strErrorHex == "C000035F")
				{
						strErrorText = "STATUS_NOT_SAFE_MODE_DRIVER";
				}
//ORIGINAL LINE: case "C0000361":
				else if (strErrorHex == "C0000361")
				{
						strErrorText = "STATUS_ACCESS_DISABLED_BY_POLICY_DEFAULT";
				}
//ORIGINAL LINE: case "C0000362":
				else if (strErrorHex == "C0000362")
				{
						strErrorText = "STATUS_ACCESS_DISABLED_BY_POLICY_PATH";
				}
//ORIGINAL LINE: case "C0000363":
				else if (strErrorHex == "C0000363")
				{
						strErrorText = "STATUS_ACCESS_DISABLED_BY_POLICY_PUBLISHER";
				}
//ORIGINAL LINE: case "C0000364":
				else if (strErrorHex == "C0000364")
				{
						strErrorText = "STATUS_ACCESS_DISABLED_BY_POLICY_OTHER";
				}
//ORIGINAL LINE: case "C0000365":
				else if (strErrorHex == "C0000365")
				{
						strErrorText = "STATUS_FAILED_DRIVER_ENTRY";
				}
//ORIGINAL LINE: case "C0000366":
				else if (strErrorHex == "C0000366")
				{
						strErrorText = "STATUS_DEVICE_ENUMERATION_ERROR";
				}
//ORIGINAL LINE: case "00000367":
				else if (strErrorHex == "00000367")
				{
						strErrorText = "STATUS_WAIT_FOR_OPLOCK";
				}
//ORIGINAL LINE: case "C0000368":
				else if (strErrorHex == "C0000368")
				{
						strErrorText = "STATUS_MOUNT_POINT_NOT_RESOLVED";
				}
//ORIGINAL LINE: case "C0000369":
				else if (strErrorHex == "C0000369")
				{
						strErrorText = "STATUS_INVALID_DEVICE_OBJECT_PARAMETER";
				}
//ORIGINAL LINE: case "C000036A":
				else if (strErrorHex == "C000036A")
				{
						strErrorText = "STATUS_MCA_OCCURED";
				}
//ORIGINAL LINE: case "C000036B":
				else if (strErrorHex == "C000036B")
				{
						strErrorText = "STATUS_DRIVER_BLOCKED_CRITICAL";
				}
//ORIGINAL LINE: case "C000036C":
				else if (strErrorHex == "C000036C")
				{
						strErrorText = "STATUS_DRIVER_BLOCKED";
				}
//ORIGINAL LINE: case "C000036D":
				else if (strErrorHex == "C000036D")
				{
						strErrorText = "STATUS_DRIVER_DATABASE_ERROR";
				}
//ORIGINAL LINE: case "C000036E":
				else if (strErrorHex == "C000036E")
				{
						strErrorText = "STATUS_SYSTEM_HIVE_TOO_LARGE";
				}
//ORIGINAL LINE: case "C000036F":
				else if (strErrorHex == "C000036F")
				{
						strErrorText = "STATUS_INVALID_IMPORT_OF_NON_DLL";
				}
//ORIGINAL LINE: case "40000370":
				else if (strErrorHex == "40000370")
				{
						strErrorText = "STATUS_DS_SHUTTING_DOWN";
				}
//ORIGINAL LINE: case "C0000380":
				else if (strErrorHex == "C0000380")
				{
						strErrorText = "STATUS_SMARTCARD_WRONG_PIN";
				}
//ORIGINAL LINE: case "C0000381":
				else if (strErrorHex == "C0000381")
				{
						strErrorText = "STATUS_SMARTCARD_CARD_BLOCKED";
				}
//ORIGINAL LINE: case "C0000382":
				else if (strErrorHex == "C0000382")
				{
						strErrorText = "STATUS_SMARTCARD_CARD_NOT_AUTHENTICATED";
				}
//ORIGINAL LINE: case "C0000383":
				else if (strErrorHex == "C0000383")
				{
						strErrorText = "STATUS_SMARTCARD_NO_CARD";
				}
//ORIGINAL LINE: case "C0000384":
				else if (strErrorHex == "C0000384")
				{
						strErrorText = "STATUS_SMARTCARD_NO_KEY_CONTAINER";
				}
//ORIGINAL LINE: case "C0000385":
				else if (strErrorHex == "C0000385")
				{
						strErrorText = "STATUS_SMARTCARD_NO_CERTIFICATE";
				}
//ORIGINAL LINE: case "C0000386":
				else if (strErrorHex == "C0000386")
				{
						strErrorText = "STATUS_SMARTCARD_NO_KEYSET";
				}
//ORIGINAL LINE: case "C0000387":
				else if (strErrorHex == "C0000387")
				{
						strErrorText = "STATUS_SMARTCARD_IO_ERROR";
				}
//ORIGINAL LINE: case "C0000388":
				else if (strErrorHex == "C0000388")
				{
						strErrorText = "STATUS_DOWNGRADE_DETECTED";
				}
//ORIGINAL LINE: case "C0000389":
				else if (strErrorHex == "C0000389")
				{
						strErrorText = "STATUS_SMARTCARD_CERT_REVOKED";
				}
//ORIGINAL LINE: case "C000038A":
				else if (strErrorHex == "C000038A")
				{
						strErrorText = "STATUS_ISSUING_CA_UNTRUSTED";
				}
//ORIGINAL LINE: case "C000038B":
				else if (strErrorHex == "C000038B")
				{
						strErrorText = "STATUS_REVOCATION_OFFLINE_C";
				}
//ORIGINAL LINE: case "C000038C":
				else if (strErrorHex == "C000038C")
				{
						strErrorText = "STATUS_PKINIT_CLIENT_FAILURE";
				}
//ORIGINAL LINE: case "C000038D":
				else if (strErrorHex == "C000038D")
				{
						strErrorText = "STATUS_SMARTCARD_CERT_EXPIRED";
				}
//ORIGINAL LINE: case "C000038E":
				else if (strErrorHex == "C000038E")
				{
						strErrorText = "STATUS_DRIVER_FAILED_PRIOR_UNLOAD";
				}
//ORIGINAL LINE: case "C000038F":
				else if (strErrorHex == "C000038F")
				{
						strErrorText = "STATUS_SMARTCARD_SILENT_CONTEXT";
				}
//ORIGINAL LINE: case "C0000401":
				else if (strErrorHex == "C0000401")
				{
						strErrorText = "STATUS_PER_USER_TRUST_QUOTA_EXCEEDED";
				}
//ORIGINAL LINE: case "C0000402":
				else if (strErrorHex == "C0000402")
				{
						strErrorText = "STATUS_ALL_USER_TRUST_QUOTA_EXCEEDED";
				}
//ORIGINAL LINE: case "C0000403":
				else if (strErrorHex == "C0000403")
				{
						strErrorText = "STATUS_USER_DELETE_TRUST_QUOTA_EXCEEDED";
				}
//ORIGINAL LINE: case "C0000404":
				else if (strErrorHex == "C0000404")
				{
						strErrorText = "STATUS_DS_NAME_NOT_UNIQUE";
				}
//ORIGINAL LINE: case "C0000405":
				else if (strErrorHex == "C0000405")
				{
						strErrorText = "STATUS_DS_DUPLICATE_ID_FOUND";
				}
//ORIGINAL LINE: case "C0000406":
				else if (strErrorHex == "C0000406")
				{
						strErrorText = "STATUS_DS_GROUP_CONVERSION_ERROR";
				}
//ORIGINAL LINE: case "C0000407":
				else if (strErrorHex == "C0000407")
				{
						strErrorText = "STATUS_VOLSNAP_PREPARE_HIBERNATE";
				}
//ORIGINAL LINE: case "C0000408":
				else if (strErrorHex == "C0000408")
				{
						strErrorText = "STATUS_USER2USER_REQUIRED";
				}
//ORIGINAL LINE: case "C0000409":
				else if (strErrorHex == "C0000409")
				{
						strErrorText = "STATUS_STACK_BUFFER_OVERRUN";
				}
//ORIGINAL LINE: case "C000040A":
				else if (strErrorHex == "C000040A")
				{
						strErrorText = "STATUS_NO_S4U_PROT_SUPPORT";
				}
//ORIGINAL LINE: case "C000040B":
				else if (strErrorHex == "C000040B")
				{
						strErrorText = "STATUS_CROSSREALM_DELEGATION_FAILURE";
				}
//ORIGINAL LINE: case "C000040C":
				else if (strErrorHex == "C000040C")
				{
						strErrorText = "STATUS_REVOCATION_OFFLINE_KDC";
				}
//ORIGINAL LINE: case "C000040D":
				else if (strErrorHex == "C000040D")
				{
						strErrorText = "STATUS_ISSUING_CA_UNTRUSTED_KDC";
				}
//ORIGINAL LINE: case "C000040E":
				else if (strErrorHex == "C000040E")
				{
						strErrorText = "STATUS_KDC_CERT_EXPIRED";
				}
//ORIGINAL LINE: case "C000040F":
				else if (strErrorHex == "C000040F")
				{
						strErrorText = "STATUS_KDC_CERT_REVOKED";
				}
//ORIGINAL LINE: case "C0000410":
				else if (strErrorHex == "C0000410")
				{
						strErrorText = "STATUS_PARAMETER_QUOTA_EXCEEDED";
				}
//ORIGINAL LINE: case "C0000411":
				else if (strErrorHex == "C0000411")
				{
						strErrorText = "STATUS_HIBERNATION_FAILURE";
				}
//ORIGINAL LINE: case "C0000412":
				else if (strErrorHex == "C0000412")
				{
						strErrorText = "STATUS_DELAY_LOAD_FAILED";
				}
//ORIGINAL LINE: case "C0000413":
				else if (strErrorHex == "C0000413")
				{
						strErrorText = "STATUS_AUTHENTICATION_FIREWALL_FAILED";
				}
//ORIGINAL LINE: case "C0000414":
				else if (strErrorHex == "C0000414")
				{
						strErrorText = "STATUS_VDM_DISALLOWED";
				}
//ORIGINAL LINE: case "C0000415":
				else if (strErrorHex == "C0000415")
				{
						strErrorText = "STATUS_HUNG_DISPLAY_DRIVER_THREAD";
				}
//ORIGINAL LINE: case "C0009898":
				else if (strErrorHex == "C0009898")
				{
						strErrorText = "STATUS_WOW_ASSERTION";
				}
//ORIGINAL LINE: case "C0010001":
				else if (strErrorHex == "C0010001")
				{
						strErrorText = "DBG_NO_STATE_CHANGE";
				}
//ORIGINAL LINE: case "C0010002":
				else if (strErrorHex == "C0010002")
				{
						strErrorText = "DBG_APP_NOT_IDLE";
				}
//ORIGINAL LINE: case "C0020001":
				else if (strErrorHex == "C0020001")
				{
						strErrorText = "RPC_NT_INVALID_STRING_BINDING";
				}
//ORIGINAL LINE: case "C0020002":
				else if (strErrorHex == "C0020002")
				{
						strErrorText = "RPC_NT_WRONG_KIND_OF_BINDING";
				}
//ORIGINAL LINE: case "C0020003":
				else if (strErrorHex == "C0020003")
				{
						strErrorText = "RPC_NT_INVALID_BINDING";
				}
//ORIGINAL LINE: case "C0020004":
				else if (strErrorHex == "C0020004")
				{
						strErrorText = "RPC_NT_PROTSEQ_NOT_SUPPORTED";
				}
//ORIGINAL LINE: case "C0020005":
				else if (strErrorHex == "C0020005")
				{
						strErrorText = "RPC_NT_INVALID_RPC_PROTSEQ";
				}
//ORIGINAL LINE: case "C0020006":
				else if (strErrorHex == "C0020006")
				{
						strErrorText = "RPC_NT_INVALID_STRING_UUID";
				}
//ORIGINAL LINE: case "C0020007":
				else if (strErrorHex == "C0020007")
				{
						strErrorText = "RPC_NT_INVALID_ENDPOINT_FORMAT";
				}
//ORIGINAL LINE: case "C0020008":
				else if (strErrorHex == "C0020008")
				{
						strErrorText = "RPC_NT_INVALID_NET_ADDR";
				}
//ORIGINAL LINE: case "C0020009":
				else if (strErrorHex == "C0020009")
				{
						strErrorText = "RPC_NT_NO_ENDPOINT_FOUND";
				}
//ORIGINAL LINE: case "C002000A":
				else if (strErrorHex == "C002000A")
				{
						strErrorText = "RPC_NT_INVALID_TIMEOUT";
				}
//ORIGINAL LINE: case "C002000B":
				else if (strErrorHex == "C002000B")
				{
						strErrorText = "RPC_NT_OBJECT_NOT_FOUND";
				}
//ORIGINAL LINE: case "C002000C":
				else if (strErrorHex == "C002000C")
				{
						strErrorText = "RPC_NT_ALREADY_REGISTERED";
				}
//ORIGINAL LINE: case "C002000D":
				else if (strErrorHex == "C002000D")
				{
						strErrorText = "RPC_NT_TYPE_ALREADY_REGISTERED";
				}
//ORIGINAL LINE: case "C002000E":
				else if (strErrorHex == "C002000E")
				{
						strErrorText = "RPC_NT_ALREADY_LISTENING";
				}
//ORIGINAL LINE: case "C002000F":
				else if (strErrorHex == "C002000F")
				{
						strErrorText = "RPC_NT_NO_PROTSEQS_REGISTERED";
				}
//ORIGINAL LINE: case "C0020010":
				else if (strErrorHex == "C0020010")
				{
						strErrorText = "RPC_NT_NOT_LISTENING";
				}
//ORIGINAL LINE: case "C0020011":
				else if (strErrorHex == "C0020011")
				{
						strErrorText = "RPC_NT_UNKNOWN_MGR_TYPE";
				}
//ORIGINAL LINE: case "C0020012":
				else if (strErrorHex == "C0020012")
				{
						strErrorText = "RPC_NT_UNKNOWN_IF";
				}
//ORIGINAL LINE: case "C0020013":
				else if (strErrorHex == "C0020013")
				{
						strErrorText = "RPC_NT_NO_BINDINGS";
				}
//ORIGINAL LINE: case "C0020014":
				else if (strErrorHex == "C0020014")
				{
						strErrorText = "RPC_NT_NO_PROTSEQS";
				}
//ORIGINAL LINE: case "C0020015":
				else if (strErrorHex == "C0020015")
				{
						strErrorText = "RPC_NT_CANT_CREATE_ENDPOINT";
				}
//ORIGINAL LINE: case "C0020016":
				else if (strErrorHex == "C0020016")
				{
						strErrorText = "RPC_NT_OUT_OF_RESOURCES";
				}
//ORIGINAL LINE: case "C0020017":
				else if (strErrorHex == "C0020017")
				{
						strErrorText = "RPC_NT_SERVER_UNAVAILABLE";
				}
//ORIGINAL LINE: case "C0020018":
				else if (strErrorHex == "C0020018")
				{
						strErrorText = "RPC_NT_SERVER_TOO_BUSY";
				}
//ORIGINAL LINE: case "C0020019":
				else if (strErrorHex == "C0020019")
				{
						strErrorText = "RPC_NT_INVALID_NETWORK_OPTIONS";
				}
//ORIGINAL LINE: case "C002001A":
				else if (strErrorHex == "C002001A")
				{
						strErrorText = "RPC_NT_NO_CALL_ACTIVE";
				}
//ORIGINAL LINE: case "C002001B":
				else if (strErrorHex == "C002001B")
				{
						strErrorText = "RPC_NT_CALL_FAILED";
				}
//ORIGINAL LINE: case "C002001C":
				else if (strErrorHex == "C002001C")
				{
						strErrorText = "RPC_NT_CALL_FAILED_DNE";
				}
//ORIGINAL LINE: case "C002001D":
				else if (strErrorHex == "C002001D")
				{
						strErrorText = "RPC_NT_PROTOCOL_ERROR";
				}
//ORIGINAL LINE: case "C002001F":
				else if (strErrorHex == "C002001F")
				{
						strErrorText = "RPC_NT_UNSUPPORTED_TRANS_SYN";
				}
//ORIGINAL LINE: case "C0020021":
				else if (strErrorHex == "C0020021")
				{
						strErrorText = "RPC_NT_UNSUPPORTED_TYPE";
				}
//ORIGINAL LINE: case "C0020022":
				else if (strErrorHex == "C0020022")
				{
						strErrorText = "RPC_NT_INVALID_TAG";
				}
//ORIGINAL LINE: case "C0020023":
				else if (strErrorHex == "C0020023")
				{
						strErrorText = "RPC_NT_INVALID_BOUND";
				}
//ORIGINAL LINE: case "C0020024":
				else if (strErrorHex == "C0020024")
				{
						strErrorText = "RPC_NT_NO_ENTRY_NAME";
				}
//ORIGINAL LINE: case "C0020025":
				else if (strErrorHex == "C0020025")
				{
						strErrorText = "RPC_NT_INVALID_NAME_SYNTAX";
				}
//ORIGINAL LINE: case "C0020026":
				else if (strErrorHex == "C0020026")
				{
						strErrorText = "RPC_NT_UNSUPPORTED_NAME_SYNTAX";
				}
//ORIGINAL LINE: case "C0020028":
				else if (strErrorHex == "C0020028")
				{
						strErrorText = "RPC_NT_UUID_NO_ADDRESS";
				}
//ORIGINAL LINE: case "C0020029":
				else if (strErrorHex == "C0020029")
				{
						strErrorText = "RPC_NT_DUPLICATE_ENDPOINT";
				}
//ORIGINAL LINE: case "C002002A":
				else if (strErrorHex == "C002002A")
				{
						strErrorText = "RPC_NT_UNKNOWN_AUTHN_TYPE";
				}
//ORIGINAL LINE: case "C002002B":
				else if (strErrorHex == "C002002B")
				{
						strErrorText = "RPC_NT_MAX_CALLS_TOO_SMALL";
				}
//ORIGINAL LINE: case "C002002C":
				else if (strErrorHex == "C002002C")
				{
						strErrorText = "RPC_NT_STRING_TOO_LONG";
				}
//ORIGINAL LINE: case "C002002D":
				else if (strErrorHex == "C002002D")
				{
						strErrorText = "RPC_NT_PROTSEQ_NOT_FOUND";
				}
//ORIGINAL LINE: case "C002002E":
				else if (strErrorHex == "C002002E")
				{
						strErrorText = "RPC_NT_PROCNUM_OUT_OF_RANGE";
				}
//ORIGINAL LINE: case "C002002F":
				else if (strErrorHex == "C002002F")
				{
						strErrorText = "RPC_NT_BINDING_HAS_NO_AUTH";
				}
//ORIGINAL LINE: case "C0020030":
				else if (strErrorHex == "C0020030")
				{
						strErrorText = "RPC_NT_UNKNOWN_AUTHN_SERVICE";
				}
//ORIGINAL LINE: case "C0020031":
				else if (strErrorHex == "C0020031")
				{
						strErrorText = "RPC_NT_UNKNOWN_AUTHN_LEVEL";
				}
//ORIGINAL LINE: case "C0020032":
				else if (strErrorHex == "C0020032")
				{
						strErrorText = "RPC_NT_INVALID_AUTH_IDENTITY";
				}
//ORIGINAL LINE: case "C0020033":
				else if (strErrorHex == "C0020033")
				{
						strErrorText = "RPC_NT_UNKNOWN_AUTHZ_SERVICE";
				}
//ORIGINAL LINE: case "C0020034":
				else if (strErrorHex == "C0020034")
				{
						strErrorText = "EPT_NT_INVALID_ENTRY";
				}
//ORIGINAL LINE: case "C0020035":
				else if (strErrorHex == "C0020035")
				{
						strErrorText = "EPT_NT_CANT_PERFORM_OP";
				}
//ORIGINAL LINE: case "C0020036":
				else if (strErrorHex == "C0020036")
				{
						strErrorText = "EPT_NT_NOT_REGISTERED";
				}
//ORIGINAL LINE: case "C0020037":
				else if (strErrorHex == "C0020037")
				{
						strErrorText = "RPC_NT_NOTHING_TO_EXPORT";
				}
//ORIGINAL LINE: case "C0020038":
				else if (strErrorHex == "C0020038")
				{
						strErrorText = "RPC_NT_INCOMPLETE_NAME";
				}
//ORIGINAL LINE: case "C0020039":
				else if (strErrorHex == "C0020039")
				{
						strErrorText = "RPC_NT_INVALID_VERS_OPTION";
				}
//ORIGINAL LINE: case "C002003A":
				else if (strErrorHex == "C002003A")
				{
						strErrorText = "RPC_NT_NO_MORE_MEMBERS";
				}
//ORIGINAL LINE: case "C002003B":
				else if (strErrorHex == "C002003B")
				{
						strErrorText = "RPC_NT_NOT_ALL_OBJS_UNEXPORTED";
				}
//ORIGINAL LINE: case "C002003C":
				else if (strErrorHex == "C002003C")
				{
						strErrorText = "RPC_NT_INTERFACE_NOT_FOUND";
				}
//ORIGINAL LINE: case "C002003D":
				else if (strErrorHex == "C002003D")
				{
						strErrorText = "RPC_NT_ENTRY_ALREADY_EXISTS";
				}
//ORIGINAL LINE: case "C002003E":
				else if (strErrorHex == "C002003E")
				{
						strErrorText = "RPC_NT_ENTRY_NOT_FOUND";
				}
//ORIGINAL LINE: case "C002003F":
				else if (strErrorHex == "C002003F")
				{
						strErrorText = "RPC_NT_NAME_SERVICE_UNAVAILABLE";
				}
//ORIGINAL LINE: case "C0020040":
				else if (strErrorHex == "C0020040")
				{
						strErrorText = "RPC_NT_INVALID_NAF_ID";
				}
//ORIGINAL LINE: case "C0020041":
				else if (strErrorHex == "C0020041")
				{
						strErrorText = "RPC_NT_CANNOT_SUPPORT";
				}
//ORIGINAL LINE: case "C0020042":
				else if (strErrorHex == "C0020042")
				{
						strErrorText = "RPC_NT_NO_CONTEXT_AVAILABLE";
				}
//ORIGINAL LINE: case "C0020043":
				else if (strErrorHex == "C0020043")
				{
						strErrorText = "RPC_NT_INTERNAL_ERROR";
				}
//ORIGINAL LINE: case "C0020044":
				else if (strErrorHex == "C0020044")
				{
						strErrorText = "RPC_NT_ZERO_DIVIDE";
				}
//ORIGINAL LINE: case "C0020045":
				else if (strErrorHex == "C0020045")
				{
						strErrorText = "RPC_NT_ADDRESS_ERROR";
				}
//ORIGINAL LINE: case "C0020046":
				else if (strErrorHex == "C0020046")
				{
						strErrorText = "RPC_NT_FP_DIV_ZERO";
				}
//ORIGINAL LINE: case "C0020047":
				else if (strErrorHex == "C0020047")
				{
						strErrorText = "RPC_NT_FP_UNDERFLOW";
				}
//ORIGINAL LINE: case "C0020048":
				else if (strErrorHex == "C0020048")
				{
						strErrorText = "RPC_NT_FP_OVERFLOW";
				}
//ORIGINAL LINE: case "C0030001":
				else if (strErrorHex == "C0030001")
				{
						strErrorText = "RPC_NT_NO_MORE_ENTRIES";
				}
//ORIGINAL LINE: case "C0030002":
				else if (strErrorHex == "C0030002")
				{
						strErrorText = "RPC_NT_SS_CHAR_TRANS_OPEN_FAIL";
				}
//ORIGINAL LINE: case "C0030003":
				else if (strErrorHex == "C0030003")
				{
						strErrorText = "RPC_NT_SS_CHAR_TRANS_SHORT_FILE";
				}
//ORIGINAL LINE: case "C0030004":
				else if (strErrorHex == "C0030004")
				{
						strErrorText = "RPC_NT_SS_IN_NULL_CONTEXT";
				}
//ORIGINAL LINE: case "C0030005":
				else if (strErrorHex == "C0030005")
				{
						strErrorText = "RPC_NT_SS_CONTEXT_MISMATCH";
				}
//ORIGINAL LINE: case "C0030006":
				else if (strErrorHex == "C0030006")
				{
						strErrorText = "RPC_NT_SS_CONTEXT_DAMAGED";
				}
//ORIGINAL LINE: case "C0030007":
				else if (strErrorHex == "C0030007")
				{
						strErrorText = "RPC_NT_SS_HANDLES_MISMATCH";
				}
//ORIGINAL LINE: case "C0030008":
				else if (strErrorHex == "C0030008")
				{
						strErrorText = "RPC_NT_SS_CANNOT_GET_CALL_HANDLE";
				}
//ORIGINAL LINE: case "C0030009":
				else if (strErrorHex == "C0030009")
				{
						strErrorText = "RPC_NT_NULL_REF_POINTER";
				}
//ORIGINAL LINE: case "C003000A":
				else if (strErrorHex == "C003000A")
				{
						strErrorText = "RPC_NT_ENUM_VALUE_OUT_OF_RANGE";
				}
//ORIGINAL LINE: case "C003000B":
				else if (strErrorHex == "C003000B")
				{
						strErrorText = "RPC_NT_BYTE_COUNT_TOO_SMALL";
				}
//ORIGINAL LINE: case "C003000C":
				else if (strErrorHex == "C003000C")
				{
						strErrorText = "RPC_NT_BAD_STUB_DATA";
				}
//ORIGINAL LINE: case "C0020049":
				else if (strErrorHex == "C0020049")
				{
						strErrorText = "RPC_NT_CALL_IN_PROGRESS";
				}
//ORIGINAL LINE: case "C002004A":
				else if (strErrorHex == "C002004A")
				{
						strErrorText = "RPC_NT_NO_MORE_BINDINGS";
				}
//ORIGINAL LINE: case "C002004B":
				else if (strErrorHex == "C002004B")
				{
						strErrorText = "RPC_NT_GROUP_MEMBER_NOT_FOUND";
				}
//ORIGINAL LINE: case "C002004C":
				else if (strErrorHex == "C002004C")
				{
						strErrorText = "EPT_NT_CANT_CREATE";
				}
//ORIGINAL LINE: case "C002004D":
				else if (strErrorHex == "C002004D")
				{
						strErrorText = "RPC_NT_INVALID_OBJECT";
				}
//ORIGINAL LINE: case "C002004F":
				else if (strErrorHex == "C002004F")
				{
						strErrorText = "RPC_NT_NO_INTERFACES";
				}
//ORIGINAL LINE: case "C0020050":
				else if (strErrorHex == "C0020050")
				{
						strErrorText = "RPC_NT_CALL_CANCELLED";
				}
//ORIGINAL LINE: case "C0020051":
				else if (strErrorHex == "C0020051")
				{
						strErrorText = "RPC_NT_BINDING_INCOMPLETE";
				}
//ORIGINAL LINE: case "C0020052":
				else if (strErrorHex == "C0020052")
				{
						strErrorText = "RPC_NT_COMM_FAILURE";
				}
//ORIGINAL LINE: case "C0020053":
				else if (strErrorHex == "C0020053")
				{
						strErrorText = "RPC_NT_UNSUPPORTED_AUTHN_LEVEL";
				}
//ORIGINAL LINE: case "C0020054":
				else if (strErrorHex == "C0020054")
				{
						strErrorText = "RPC_NT_NO_PRINC_NAME";
				}
//ORIGINAL LINE: case "C0020055":
				else if (strErrorHex == "C0020055")
				{
						strErrorText = "RPC_NT_NOT_RPC_ERROR";
				}
//ORIGINAL LINE: case "40020056":
				else if (strErrorHex == "40020056")
				{
						strErrorText = "RPC_NT_UUID_LOCAL_ONLY";
				}
//ORIGINAL LINE: case "C0020057":
				else if (strErrorHex == "C0020057")
				{
						strErrorText = "RPC_NT_SEC_PKG_ERROR";
				}
//ORIGINAL LINE: case "C0020058":
				else if (strErrorHex == "C0020058")
				{
						strErrorText = "RPC_NT_NOT_CANCELLED";
				}
//ORIGINAL LINE: case "C0030059":
				else if (strErrorHex == "C0030059")
				{
						strErrorText = "RPC_NT_INVALID_ES_ACTION";
				}
//ORIGINAL LINE: case "C003005A":
				else if (strErrorHex == "C003005A")
				{
						strErrorText = "RPC_NT_WRONG_ES_VERSION";
				}
//ORIGINAL LINE: case "C003005B":
				else if (strErrorHex == "C003005B")
				{
						strErrorText = "RPC_NT_WRONG_STUB_VERSION";
				}
//ORIGINAL LINE: case "C003005C":
				else if (strErrorHex == "C003005C")
				{
						strErrorText = "RPC_NT_INVALID_PIPE_OBJECT";
				}
//ORIGINAL LINE: case "C003005D":
				else if (strErrorHex == "C003005D")
				{
						strErrorText = "RPC_NT_INVALID_PIPE_OPERATION";
				}
//ORIGINAL LINE: case "C003005E":
				else if (strErrorHex == "C003005E")
				{
						strErrorText = "RPC_NT_WRONG_PIPE_VERSION";
				}
//ORIGINAL LINE: case "C003005F":
				else if (strErrorHex == "C003005F")
				{
						strErrorText = "RPC_NT_PIPE_CLOSED";
				}
//ORIGINAL LINE: case "C0030060":
				else if (strErrorHex == "C0030060")
				{
						strErrorText = "RPC_NT_PIPE_DISCIPLINE_ERROR";
				}
//ORIGINAL LINE: case "C0030061":
				else if (strErrorHex == "C0030061")
				{
						strErrorText = "RPC_NT_PIPE_EMPTY";
				}
//ORIGINAL LINE: case "C0020062":
				else if (strErrorHex == "C0020062")
				{
						strErrorText = "RPC_NT_INVALID_ASYNC_HANDLE";
				}
//ORIGINAL LINE: case "C0020063":
				else if (strErrorHex == "C0020063")
				{
						strErrorText = "RPC_NT_INVALID_ASYNC_CALL";
				}
//ORIGINAL LINE: case "400200AF":
				else if (strErrorHex == "400200AF")
				{
						strErrorText = "RPC_NT_SEND_INCOMPLETE";
				}
//ORIGINAL LINE: case "C0140001":
				else if (strErrorHex == "C0140001")
				{
						strErrorText = "STATUS_ACPI_INVALID_OPCODE";
				}
//ORIGINAL LINE: case "C0140002":
				else if (strErrorHex == "C0140002")
				{
						strErrorText = "STATUS_ACPI_STACK_OVERFLOW";
				}
//ORIGINAL LINE: case "C0140003":
				else if (strErrorHex == "C0140003")
				{
						strErrorText = "STATUS_ACPI_ASSERT_FAILED";
				}
//ORIGINAL LINE: case "C0140004":
				else if (strErrorHex == "C0140004")
				{
						strErrorText = "STATUS_ACPI_INVALID_INDEX";
				}
//ORIGINAL LINE: case "C0140005":
				else if (strErrorHex == "C0140005")
				{
						strErrorText = "STATUS_ACPI_INVALID_ARGUMENT";
				}
//ORIGINAL LINE: case "C0140006":
				else if (strErrorHex == "C0140006")
				{
						strErrorText = "STATUS_ACPI_FATAL";
				}
//ORIGINAL LINE: case "C0140007":
				else if (strErrorHex == "C0140007")
				{
						strErrorText = "STATUS_ACPI_INVALID_SUPERNAME";
				}
//ORIGINAL LINE: case "C0140008":
				else if (strErrorHex == "C0140008")
				{
						strErrorText = "STATUS_ACPI_INVALID_ARGTYPE";
				}
//ORIGINAL LINE: case "C0140009":
				else if (strErrorHex == "C0140009")
				{
						strErrorText = "STATUS_ACPI_INVALID_OBJTYPE";
				}
//ORIGINAL LINE: case "C014000A":
				else if (strErrorHex == "C014000A")
				{
						strErrorText = "STATUS_ACPI_INVALID_TARGETTYPE";
				}
//ORIGINAL LINE: case "C014000B":
				else if (strErrorHex == "C014000B")
				{
						strErrorText = "STATUS_ACPI_INCORRECT_ARGUMENT_COUNT";
				}
//ORIGINAL LINE: case "C014000C":
				else if (strErrorHex == "C014000C")
				{
						strErrorText = "STATUS_ACPI_ADDRESS_NOT_MAPPED";
				}
//ORIGINAL LINE: case "C014000D":
				else if (strErrorHex == "C014000D")
				{
						strErrorText = "STATUS_ACPI_INVALID_EVENTTYPE";
				}
//ORIGINAL LINE: case "C014000E":
				else if (strErrorHex == "C014000E")
				{
						strErrorText = "STATUS_ACPI_HANDLER_COLLISION";
				}
//ORIGINAL LINE: case "C014000F":
				else if (strErrorHex == "C014000F")
				{
						strErrorText = "STATUS_ACPI_INVALID_DATA";
				}
//ORIGINAL LINE: case "C0140010":
				else if (strErrorHex == "C0140010")
				{
						strErrorText = "STATUS_ACPI_INVALID_REGION";
				}
//ORIGINAL LINE: case "C0140011":
				else if (strErrorHex == "C0140011")
				{
						strErrorText = "STATUS_ACPI_INVALID_ACCESS_SIZE";
				}
//ORIGINAL LINE: case "C0140012":
				else if (strErrorHex == "C0140012")
				{
						strErrorText = "STATUS_ACPI_ACQUIRE_GLOBAL_LOCK";
				}
//ORIGINAL LINE: case "C0140013":
				else if (strErrorHex == "C0140013")
				{
						strErrorText = "STATUS_ACPI_ALREADY_INITIALIZED";
				}
//ORIGINAL LINE: case "C0140014":
				else if (strErrorHex == "C0140014")
				{
						strErrorText = "STATUS_ACPI_NOT_INITIALIZED";
				}
//ORIGINAL LINE: case "C0140015":
				else if (strErrorHex == "C0140015")
				{
						strErrorText = "STATUS_ACPI_INVALID_MUTEX_LEVEL";
				}
//ORIGINAL LINE: case "C0140016":
				else if (strErrorHex == "C0140016")
				{
						strErrorText = "STATUS_ACPI_MUTEX_NOT_OWNED";
				}
//ORIGINAL LINE: case "C0140017":
				else if (strErrorHex == "C0140017")
				{
						strErrorText = "STATUS_ACPI_MUTEX_NOT_OWNER";
				}
//ORIGINAL LINE: case "C0140018":
				else if (strErrorHex == "C0140018")
				{
						strErrorText = "STATUS_ACPI_RS_ACCESS";
				}
//ORIGINAL LINE: case "C0140019":
				else if (strErrorHex == "C0140019")
				{
						strErrorText = "STATUS_ACPI_INVALID_TABLE";
				}
//ORIGINAL LINE: case "C0140020":
				else if (strErrorHex == "C0140020")
				{
						strErrorText = "STATUS_ACPI_REG_HANDLER_FAILED";
				}
//ORIGINAL LINE: case "C0140021":
				else if (strErrorHex == "C0140021")
				{
						strErrorText = "STATUS_ACPI_POWER_REQUEST_FAILED";
				}
//ORIGINAL LINE: case "C00A0001":
				else if (strErrorHex == "C00A0001")
				{
						strErrorText = "STATUS_CTX_WINSTATION_NAME_INVALID";
				}
//ORIGINAL LINE: case "C00A0002":
				else if (strErrorHex == "C00A0002")
				{
						strErrorText = "STATUS_CTX_INVALID_PD";
				}
//ORIGINAL LINE: case "C00A0003":
				else if (strErrorHex == "C00A0003")
				{
						strErrorText = "STATUS_CTX_PD_NOT_FOUND";
				}
//ORIGINAL LINE: case "400A0004":
				else if (strErrorHex == "400A0004")
				{
						strErrorText = "STATUS_CTX_CDM_CONNECT";
				}
//ORIGINAL LINE: case "400A0005":
				else if (strErrorHex == "400A0005")
				{
						strErrorText = "STATUS_CTX_CDM_DISCONNECT";
				}
//ORIGINAL LINE: case "C00A0006":
				else if (strErrorHex == "C00A0006")
				{
						strErrorText = "STATUS_CTX_CLOSE_PENDING";
				}
//ORIGINAL LINE: case "C00A0007":
				else if (strErrorHex == "C00A0007")
				{
						strErrorText = "STATUS_CTX_NO_OUTBUF";
				}
//ORIGINAL LINE: case "C00A0008":
				else if (strErrorHex == "C00A0008")
				{
						strErrorText = "STATUS_CTX_MODEM_INF_NOT_FOUND";
				}
//ORIGINAL LINE: case "C00A0009":
				else if (strErrorHex == "C00A0009")
				{
						strErrorText = "STATUS_CTX_INVALID_MODEMNAME";
				}
//ORIGINAL LINE: case "C00A000A":
				else if (strErrorHex == "C00A000A")
				{
						strErrorText = "STATUS_CTX_RESPONSE_ERROR";
				}
//ORIGINAL LINE: case "C00A000B":
				else if (strErrorHex == "C00A000B")
				{
						strErrorText = "STATUS_CTX_MODEM_RESPONSE_TIMEOUT";
				}
//ORIGINAL LINE: case "C00A000C":
				else if (strErrorHex == "C00A000C")
				{
						strErrorText = "STATUS_CTX_MODEM_RESPONSE_NO_CARRIER";
				}
//ORIGINAL LINE: case "C00A000D":
				else if (strErrorHex == "C00A000D")
				{
						strErrorText = "STATUS_CTX_MODEM_RESPONSE_NO_DIALTONE";
				}
//ORIGINAL LINE: case "C00A000E":
				else if (strErrorHex == "C00A000E")
				{
						strErrorText = "STATUS_CTX_MODEM_RESPONSE_BUSY";
				}
//ORIGINAL LINE: case "C00A000F":
				else if (strErrorHex == "C00A000F")
				{
						strErrorText = "STATUS_CTX_MODEM_RESPONSE_VOICE";
				}
//ORIGINAL LINE: case "C00A0010":
				else if (strErrorHex == "C00A0010")
				{
						strErrorText = "STATUS_CTX_TD_ERROR";
				}
//ORIGINAL LINE: case "C00A0012":
				else if (strErrorHex == "C00A0012")
				{
						strErrorText = "STATUS_CTX_LICENSE_CLIENT_INVALID";
				}
//ORIGINAL LINE: case "C00A0013":
				else if (strErrorHex == "C00A0013")
				{
						strErrorText = "STATUS_CTX_LICENSE_NOT_AVAILABLE";
				}
//ORIGINAL LINE: case "C00A0014":
				else if (strErrorHex == "C00A0014")
				{
						strErrorText = "STATUS_CTX_LICENSE_EXPIRED";
				}
//ORIGINAL LINE: case "C00A0015":
				else if (strErrorHex == "C00A0015")
				{
						strErrorText = "STATUS_CTX_WINSTATION_NOT_FOUND";
				}
//ORIGINAL LINE: case "C00A0016":
				else if (strErrorHex == "C00A0016")
				{
						strErrorText = "STATUS_CTX_WINSTATION_NAME_COLLISION";
				}
//ORIGINAL LINE: case "C00A0017":
				else if (strErrorHex == "C00A0017")
				{
						strErrorText = "STATUS_CTX_WINSTATION_BUSY";
				}
//ORIGINAL LINE: case "C00A0018":
				else if (strErrorHex == "C00A0018")
				{
						strErrorText = "STATUS_CTX_BAD_VIDEO_MODE";
				}
//ORIGINAL LINE: case "C00A0022":
				else if (strErrorHex == "C00A0022")
				{
						strErrorText = "STATUS_CTX_GRAPHICS_INVALID";
				}
//ORIGINAL LINE: case "C00A0024":
				else if (strErrorHex == "C00A0024")
				{
						strErrorText = "STATUS_CTX_NOT_CONSOLE";
				}
//ORIGINAL LINE: case "C00A0026":
				else if (strErrorHex == "C00A0026")
				{
						strErrorText = "STATUS_CTX_CLIENT_QUERY_TIMEOUT";
				}
//ORIGINAL LINE: case "C00A0027":
				else if (strErrorHex == "C00A0027")
				{
						strErrorText = "STATUS_CTX_CONSOLE_DISCONNECT";
				}
//ORIGINAL LINE: case "C00A0028":
				else if (strErrorHex == "C00A0028")
				{
						strErrorText = "STATUS_CTX_CONSOLE_CONNECT";
				}
//ORIGINAL LINE: case "C00A002A":
				else if (strErrorHex == "C00A002A")
				{
						strErrorText = "STATUS_CTX_SHADOW_DENIED";
				}
//ORIGINAL LINE: case "C00A002B":
				else if (strErrorHex == "C00A002B")
				{
						strErrorText = "STATUS_CTX_WINSTATION_ACCESS_DENIED";
				}
//ORIGINAL LINE: case "C00A002E":
				else if (strErrorHex == "C00A002E")
				{
						strErrorText = "STATUS_CTX_INVALID_WD";
				}
//ORIGINAL LINE: case "C00A002F":
				else if (strErrorHex == "C00A002F")
				{
						strErrorText = "STATUS_CTX_WD_NOT_FOUND";
				}
//ORIGINAL LINE: case "C00A0030":
				else if (strErrorHex == "C00A0030")
				{
						strErrorText = "STATUS_CTX_SHADOW_INVALID";
				}
//ORIGINAL LINE: case "C00A0031":
				else if (strErrorHex == "C00A0031")
				{
						strErrorText = "STATUS_CTX_SHADOW_DISABLED";
				}
//ORIGINAL LINE: case "C00A0032":
				else if (strErrorHex == "C00A0032")
				{
						strErrorText = "STATUS_RDP_PROTOCOL_ERROR";
				}
//ORIGINAL LINE: case "C00A0033":
				else if (strErrorHex == "C00A0033")
				{
						strErrorText = "STATUS_CTX_CLIENT_LICENSE_NOT_SET";
				}
//ORIGINAL LINE: case "C00A0034":
				else if (strErrorHex == "C00A0034")
				{
						strErrorText = "STATUS_CTX_CLIENT_LICENSE_IN_USE";
				}
//ORIGINAL LINE: case "C00A0035":
				else if (strErrorHex == "C00A0035")
				{
						strErrorText = "STATUS_CTX_SHADOW_ENDED_BY_MODE_CHANGE";
				}
//ORIGINAL LINE: case "C00A0036":
				else if (strErrorHex == "C00A0036")
				{
						strErrorText = "STATUS_CTX_SHADOW_NOT_RUNNING";
				}
//ORIGINAL LINE: case "C0040035":
				else if (strErrorHex == "C0040035")
				{
						strErrorText = "STATUS_PNP_BAD_MPS_TABLE";
				}
//ORIGINAL LINE: case "C0040036":
				else if (strErrorHex == "C0040036")
				{
						strErrorText = "STATUS_PNP_TRANSLATION_FAILED";
				}
//ORIGINAL LINE: case "C0040037":
				else if (strErrorHex == "C0040037")
				{
						strErrorText = "STATUS_PNP_IRQ_TRANSLATION_FAILED";
				}
//ORIGINAL LINE: case "C0040038":
				else if (strErrorHex == "C0040038")
				{
						strErrorText = "STATUS_PNP_INVALID_ID";
				}
//ORIGINAL LINE: case "C0150001":
				else if (strErrorHex == "C0150001")
				{
						strErrorText = "STATUS_SXS_SECTION_NOT_FOUND";
				}
//ORIGINAL LINE: case "C0150002":
				else if (strErrorHex == "C0150002")
				{
						strErrorText = "STATUS_SXS_CANT_GEN_ACTCTX";
				}
//ORIGINAL LINE: case "C0150003":
				else if (strErrorHex == "C0150003")
				{
						strErrorText = "STATUS_SXS_INVALID_ACTCTXDATA_FORMAT";
				}
//ORIGINAL LINE: case "C0150004":
				else if (strErrorHex == "C0150004")
				{
						strErrorText = "STATUS_SXS_ASSEMBLY_NOT_FOUND";
				}
//ORIGINAL LINE: case "C0150005":
				else if (strErrorHex == "C0150005")
				{
						strErrorText = "STATUS_SXS_MANIFEST_FORMAT_ERROR";
				}
//ORIGINAL LINE: case "C0150006":
				else if (strErrorHex == "C0150006")
				{
						strErrorText = "STATUS_SXS_MANIFEST_PARSE_ERROR";
				}
//ORIGINAL LINE: case "C0150007":
				else if (strErrorHex == "C0150007")
				{
						strErrorText = "STATUS_SXS_ACTIVATION_CONTEXT_DISABLED";
				}
//ORIGINAL LINE: case "C0150008":
				else if (strErrorHex == "C0150008")
				{
						strErrorText = "STATUS_SXS_KEY_NOT_FOUND";
				}
//ORIGINAL LINE: case "C0150009":
				else if (strErrorHex == "C0150009")
				{
						strErrorText = "STATUS_SXS_VERSION_CONFLICT";
				}
//ORIGINAL LINE: case "C015000A":
				else if (strErrorHex == "C015000A")
				{
						strErrorText = "STATUS_SXS_WRONG_SECTION_TYPE";
				}
//ORIGINAL LINE: case "C015000B":
				else if (strErrorHex == "C015000B")
				{
						strErrorText = "STATUS_SXS_THREAD_QUERIES_DISABLED";
				}
//ORIGINAL LINE: case "C015000C":
				else if (strErrorHex == "C015000C")
				{
						strErrorText = "STATUS_SXS_ASSEMBLY_MISSING";
				}
//ORIGINAL LINE: case "4015000D":
				else if (strErrorHex == "4015000D")
				{
						strErrorText = "STATUS_SXS_RELEASE_ACTIVATION_CONTEXT";
				}
//ORIGINAL LINE: case "C015000E":
				else if (strErrorHex == "C015000E")
				{
						strErrorText = "STATUS_SXS_PROCESS_DEFAULT_ALREADY_SET";
				}
//ORIGINAL LINE: case "C015000F":
				else if (strErrorHex == "C015000F")
				{
						strErrorText = "STATUS_SXS_EARLY_DEACTIVATION";
				}
//ORIGINAL LINE: case "C0150010":
				else if (strErrorHex == "C0150010")
				{
						strErrorText = "STATUS_SXS_INVALID_DEACTIVATION";
				}
//ORIGINAL LINE: case "C0150011":
				else if (strErrorHex == "C0150011")
				{
						strErrorText = "STATUS_SXS_MULTIPLE_DEACTIVATION";
				}
//ORIGINAL LINE: case "C0150012":
				else if (strErrorHex == "C0150012")
				{
						strErrorText = "STATUS_SXS_SYSTEM_DEFAULT_ACTIVATION_CONTEXT_EMPTY";
				}
//ORIGINAL LINE: case "C0150013":
				else if (strErrorHex == "C0150013")
				{
						strErrorText = "STATUS_SXS_PROCESS_TERMINATION_REQUESTED";
				}
//ORIGINAL LINE: case "C0150014":
				else if (strErrorHex == "C0150014")
				{
						strErrorText = "STATUS_SXS_CORRUPT_ACTIVATION_STACK";
				}
//ORIGINAL LINE: case "C0150015":
				else if (strErrorHex == "C0150015")
				{
						strErrorText = "STATUS_SXS_CORRUPTION";
				}
//ORIGINAL LINE: case "C0130001":
				else if (strErrorHex == "C0130001")
				{
						strErrorText = "STATUS_CLUSTER_INVALID_NODE";
				}
//ORIGINAL LINE: case "C0130002":
				else if (strErrorHex == "C0130002")
				{
						strErrorText = "STATUS_CLUSTER_NODE_EXISTS";
				}
//ORIGINAL LINE: case "C0130003":
				else if (strErrorHex == "C0130003")
				{
						strErrorText = "STATUS_CLUSTER_JOIN_IN_PROGRESS";
				}
//ORIGINAL LINE: case "C0130004":
				else if (strErrorHex == "C0130004")
				{
						strErrorText = "STATUS_CLUSTER_NODE_NOT_FOUND";
				}
//ORIGINAL LINE: case "C0130005":
				else if (strErrorHex == "C0130005")
				{
						strErrorText = "STATUS_CLUSTER_LOCAL_NODE_NOT_FOUND";
				}
//ORIGINAL LINE: case "C0130006":
				else if (strErrorHex == "C0130006")
				{
						strErrorText = "STATUS_CLUSTER_NETWORK_EXISTS";
				}
//ORIGINAL LINE: case "C0130007":
				else if (strErrorHex == "C0130007")
				{
						strErrorText = "STATUS_CLUSTER_NETWORK_NOT_FOUND";
				}
//ORIGINAL LINE: case "C0130008":
				else if (strErrorHex == "C0130008")
				{
						strErrorText = "STATUS_CLUSTER_NETINTERFACE_EXISTS";
				}
//ORIGINAL LINE: case "C0130009":
				else if (strErrorHex == "C0130009")
				{
						strErrorText = "STATUS_CLUSTER_NETINTERFACE_NOT_FOUND";
				}
//ORIGINAL LINE: case "C013000A":
				else if (strErrorHex == "C013000A")
				{
						strErrorText = "STATUS_CLUSTER_INVALID_REQUEST";
				}
//ORIGINAL LINE: case "C013000B":
				else if (strErrorHex == "C013000B")
				{
						strErrorText = "STATUS_CLUSTER_INVALID_NETWORK_PROVIDER";
				}
//ORIGINAL LINE: case "C013000C":
				else if (strErrorHex == "C013000C")
				{
						strErrorText = "STATUS_CLUSTER_NODE_DOWN";
				}
//ORIGINAL LINE: case "C013000D":
				else if (strErrorHex == "C013000D")
				{
						strErrorText = "STATUS_CLUSTER_NODE_UNREACHABLE";
				}
//ORIGINAL LINE: case "C013000E":
				else if (strErrorHex == "C013000E")
				{
						strErrorText = "STATUS_CLUSTER_NODE_NOT_MEMBER";
				}
//ORIGINAL LINE: case "C013000F":
				else if (strErrorHex == "C013000F")
				{
						strErrorText = "STATUS_CLUSTER_JOIN_NOT_IN_PROGRESS";
				}
//ORIGINAL LINE: case "C0130010":
				else if (strErrorHex == "C0130010")
				{
						strErrorText = "STATUS_CLUSTER_INVALID_NETWORK";
				}
//ORIGINAL LINE: case "C0130011":
				else if (strErrorHex == "C0130011")
				{
						strErrorText = "STATUS_CLUSTER_NO_NET_ADAPTERS";
				}
//ORIGINAL LINE: case "C0130012":
				else if (strErrorHex == "C0130012")
				{
						strErrorText = "STATUS_CLUSTER_NODE_UP";
				}
//ORIGINAL LINE: case "C0130013":
				else if (strErrorHex == "C0130013")
				{
						strErrorText = "STATUS_CLUSTER_NODE_PAUSED";
				}
//ORIGINAL LINE: case "C0130014":
				else if (strErrorHex == "C0130014")
				{
						strErrorText = "STATUS_CLUSTER_NODE_NOT_PAUSED";
				}
//ORIGINAL LINE: case "C0130015":
				else if (strErrorHex == "C0130015")
				{
						strErrorText = "STATUS_CLUSTER_NO_SECURITY_CONTEXT";
				}
//ORIGINAL LINE: case "C0130016":
				else if (strErrorHex == "C0130016")
				{
						strErrorText = "STATUS_CLUSTER_NETWORK_NOT_INTERNAL";
				}
//ORIGINAL LINE: case "C0130017":
				else if (strErrorHex == "C0130017")
				{
						strErrorText = "STATUS_CLUSTER_POISONED";
				}

				if (!strErrorText.empty())
					return "0x" + strErrorHex + " " + strErrorText + " (" + iErrorValue + ")";
				else
					return "0x" + strErrorHex + " (" + iErrorValue + ")";
			}
		}
	}
}
