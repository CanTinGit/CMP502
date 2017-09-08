## Graphics Programming(labs of CMP502)
-----
### 1. Be familiar with Windows API
#### Task
> * At first the windows is blank and bordless. Make it normal(with bord and title)
> * Add in functionality that will add / remove this window border when fullscreen or windowed mode is selected
> * Use MessageBox to show user the error information
> * Search information about Exception and Assert
> * [More][More information]: download the tutorial document

#### Solution
> * Use [**Createwindow function**][Createwindow MSDN] function with Windows Type
> * In Callback WndProc, add Case[WM_SYSCOMMAND][WM_SYSCOMMAND MSDN] to control the MAXIMIZE button(including all title buttons).
> * We can't transfer unicode string to LPCTSTR, so we can use [TEXT()][TEXT MSDN] to do it. We can also set the Character Set to Multi-Byte Character set. Properties->Configuration Properties->General
> * [**Exception**][Exception details] and [**Assert**][Assert details]

[Createwindow MSDN]: https://msdn.microsoft.com/en-us/library/windows/desktop/ms632679(v=vs.85).aspx  
[WM_SYSCOMMAND MSDN]: https://msdn.microsoft.com/en-us/library/windows/desktop/ms646360(v=vs.85).aspx  
[TEXT MSDN]: https://msdn.microsoft.com/en-us/library/dd374074(VS.85).aspx  
[Exception details]: http://www.cplusplus.com/doc/tutorial/exceptions/  
[Assert details]: http://www.cplusplus.com/reference/cassert/assert/  
[More information]: https://github.com/CanTinGit/CMP502/blob/master/Lab%201%20Framework/Tutorial1.doc  
---

### 2. Get start with Direct API
#### Task





