// myShop.cpp : Implementation of CmyShop

#include "stdafx.h"
#include "myShop.h"


// CmyShop

// This private help function winds the recordset to the given index. 
// To increase performance, we cache the current index. 
// Another improvement would be to move from currentIndex to index 
// without MoveFirst. 
// Of course, best is to select the row with Some SQL statement but 
// that is not the goal of this exercise. 

bool CmyShop::windToIndex(int index) 
{    
	if (m_currentIndex == index)// Nothing to do.   
		return true;  
	if (index < 0)   
		return false; // index too small.  
	int tmpIndex = index;  
	m_db.MoveFirst();  
	while (tmpIndex-- > 0 && m_db.MoveNext() == S_OK) {/*no op*/}  
	if (tmpIndex != -1) // index too large. Reset cached index.  
	{   
		m_currentIndex = -1;    
		return false;  
	}     
	m_currentIndex = index;  
	return true; 
}


STDMETHODIMP CmyShop::get_Count(LONG* pVal)
{
	m_currentIndex = -1;            
	m_db.MoveFirst();       
	int count = 0;            
	while (m_db.MoveNext() == S_OK) count++;            
	*pVal = count + 1;

	return S_OK;
}


STDMETHODIMP CmyShop::getNamesByIndex(LONG index, BSTR* name)
{
	if (!windToIndex(index)) return E_FAIL;  
	CComBSTR nameVal = m_db.m_ProductName;  
	return nameVal.CopyTo(name);
}


STDMETHODIMP CmyShop::getCostByIndex(LONG index, LONG* pVal)
{
	if (!windToIndex(index)) return E_FAIL;  
	*pVal = m_db.m_Price.Lo;  
	return S_OK;
}


STDMETHODIMP CmyShop::getCountByIndex(LONG index, LONG* pVal)
{
	if (!windToIndex(index)) return E_FAIL;  
	*pVal = m_db.m_ItemsinStock;
	return S_OK;
}

//Buys one piece of the item at a time 

STDMETHODIMP CmyShop::buy(LONG index)
{
	if (!windToIndex(index)) return E_FAIL;  
	if (m_db.m_ItemsinStock <= 0) return E_FAIL;  
	m_db.m_ItemsinStock--;  
	return m_db.SetData();
}
