package io.tiklab.sourcefare.project.controller;


import com.alibaba.fastjson.JSONObject;
import io.tiklab.sourcefare.common.SourceFareUtil;
import io.tiklab.sourcefare.scanner.scan.ScanExecute;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.util.ArrayList;
import java.util.List;


public class test {



	public static void main(String[] args) {
		/*String url = "https://zh-hans.eslint.org/docs/latest/rules"; // 替换为你要爬取的网页 URL

		try {
			// 连接到网页并获取 HTML 文档
			Document document = Jsoup.connect(url).get();

			// 示例：提取所有段落文本
			Elements paragraphs = document.select("p");
			for (Element paragraph : paragraphs) {
				System.out.println(paragraph.text());
			}

			// 示例：提取所有链接
			Elements links = document.select("a[href]");
			for (Element link : links) {
				System.out.println("Link: " + link.attr("href") + " Text: " + link.text());
			}
		}catch (Exception e){
			System.err.println("爬取网页时出错: " + e.getMessage());
		}*/

		String a="https://zh-hans.eslint.org/docs/latest/rules";
		String jsonObject = SourceFareUtil.restTemplateGet(a);
		System.out.println("");
	}
}
