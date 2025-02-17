package com.luky;

import java.util.LinkedList;
import java.util.List;

public class App 
{
    public static void main( String[] args )
    {
		List<String> list = new LinkedList<String>();

		try  {
			list.remove(2);
		} catch (IndexOutOfBoundsException e)  {
			System.out.printf("%s", e.toString());
		}
		System.out.printf("我执行了吗%n");
    }
}
