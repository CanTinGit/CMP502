## Graphics Programming(labs of CMP502)
-----
### 1. Be familiar with Windows API
#### Task
> * At first the windows is blank and bordless. Make it normal(with bord and title)
> * Add in functionality that will add / remove this window border when fullscreen or windowed mode is selected
> * Use MessageBox to show user the error information
> * Search information about Exception and Assert
> * [More](https://github.com/CanTinGit/CMP502/blob/master/Lab%201%20Framework/Tutorial1.doc): download the tutorial document

#### Solution
> * Use [**Createwindow function**](https://msdn.microsoft.com/en-us/library/windows/desktop/ms632679(v=vs.85).aspx) function with Windows Type
> * In Callback WndProc, add Case[**WM_SYSCOMMAND**](https://msdn.microsoft.com/en-us/library/windows/desktop/ms646360(v=vs.85).aspx  ) to control the MAXIMIZE button(including all title buttons).
> * We can't transfer unicode string to LPCTSTR, so we can use [**TEXT()**](https://msdn.microsoft.com/en-us/library/dd374074(VS.85).aspx  ) to do it. We can also set the Character Set to Multi-Byte Character set. Properties->Configuration Properties->General
> * [**Exception**](http://www.cplusplus.com/doc/tutorial/exceptions/ ) and [**Assert**](http://www.cplusplus.com/reference/cassert/assert/ )
---

### 2. Get start with Direct API
#### Task





